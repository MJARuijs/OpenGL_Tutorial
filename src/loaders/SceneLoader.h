#pragma once

#include <assimp/Importer.hpp>
#include <assimp/Scene.h>
#include <assimp/postprocess.h>

#include "../graphics/objects/Mesh.h"
#include "../graphics/objects/Entity.h"

class SceneLoader {

    struct MeshData {

        MeshData(std::vector<GLfloat>& vertices,
                 std::vector<GLfloat>& normals,
                 std::vector<GLfloat>& texCoords,
                 std::vector<GLuint>& indices) :

                vertices(vertices),
                normals(normals),
                texCoords(texCoords),
                indices(indices)
        {}

        std::vector<GLfloat> vertices;
        std::vector<GLfloat> normals;
        std::vector<GLfloat> texCoords;
        std::vector<GLuint> indices;
    };

private:
    static std::vector<MeshData> meshes;

    static void processNode(ShaderProgram& shaderProgram, aiNode *node, const aiScene *scene);
    static Mesh *processMesh(ShaderProgram& shaderProgram, aiMesh *mesh);
    static Mat4 convertMatrix(aiMatrix4x4 original);

public:
    static std::vector<Entity> load(ShaderProgram& shaderProgram, std::string filePath);

};
