#include "Skybox.h"
#include "../loaders/TextureLoader.h"

Skybox::Skybox(SkyboxMesh& skyboxMesh, std::vector<std::string>& textures) : skyboxMesh(skyboxMesh), rotation(0.f) {
    glGenTextures(1, &textureID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    for (int i = 0; i < textures.size(); i++) {
        const TextureData& texture = TextureLoader::loadData(i, textures[i]);
        glTexImage2D(static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i), 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
};

void Skybox::render() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    skyboxMesh.render();
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

Mat4 Skybox::getTransformation(float rotation) {
    Mat4 transformation;
    transformation.rotateY(rotation, transformation);
    return transformation;
}
