#include "SceneLoader.h"

std::vector<Entity> entities;

std::vector<Entity> SceneLoader::load(ShaderProgram& shaderProgram, std::string filePath) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_OptimizeGraph);

    if (!scene || scene->mFlags && AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        throw std::runtime_error("Something bad went wrong..");
    }

    std::string directory = filePath.substr(0, filePath.find_last_of('/'));

    unsigned long long int point = filePath.find_last_of('.');
    std::string fileType = filePath.substr(point, filePath.size());

    entities.clear();
    processNode(shaderProgram, scene->mRootNode, scene);
    return entities;
}

void SceneLoader::processNode(ShaderProgram& shaderProgram, aiNode *node, const aiScene *scene) {

    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        aiMaterial *aiMaterial = scene->mMaterials[mesh->mMaterialIndex];
        aiColor4D diffuse;
        aiColor4D specular;
        float shininess;
        aiGetMaterialColor(aiMaterial, AI_MATKEY_COLOR_DIFFUSE, &diffuse);
        aiGetMaterialColor(aiMaterial, AI_MATKEY_COLOR_SPECULAR, &specular);
        aiGetMaterialFloat(aiMaterial, AI_MATKEY_SHININESS, &shininess);

        float intensity = sqrtf(specular.r * specular.r + specular.g * specular.g + specular.b * specular.b);

        Material material(Color(diffuse.r, diffuse.g, diffuse.b, false), Color(specular.r, specular.g, specular.b, false), shininess, intensity);
        Entity entity(shaderProgram, processMesh(shaderProgram, mesh), material);

        entity.transformation = convertMatrix(node->mTransformation);
        entities.emplace_back(entity);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(shaderProgram, node->mChildren[i], scene);
    }

}

Mesh *SceneLoader::processMesh(ShaderProgram& shaderProgram, aiMesh *mesh) {
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texCoords;
    std::vector<GLuint> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        vertices.push_back(mesh->mVertices[i].x);
        vertices.push_back(mesh->mVertices[i].y);
        vertices.push_back(mesh->mVertices[i].z);

        normals.push_back(mesh->mNormals[i].x);
        normals.push_back(mesh->mNormals[i].y);
        normals.push_back(mesh->mNormals[i].z);

        if (mesh->mTextureCoords[0]) {
            texCoords.push_back(mesh->mTextureCoords[0][i].x);
            texCoords.push_back(mesh->mTextureCoords[0][i].y);
        }
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    return new Mesh(shaderProgram, vertices, normals, texCoords, indices);
}

Mat4 SceneLoader::convertMatrix(aiMatrix4x4 original) {
    Mat4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.matrix[i][j] = original[i][j];
        }
    }
    return result;
}
