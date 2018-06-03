#include <GL/glew.h>
#include <iostream>
#include "Texture.h"

Texture::Texture(int index, int width, int height, unsigned char* data) : index(index) {
    glGenTextures(1, &id);

    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + index));
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(TextureData* textureData) : Texture(textureData->type, textureData->width, textureData->height, textureData->data) {}

void Texture::bind() {
    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + index));
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() {
    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + index));
    glBindTexture(GL_TEXTURE_2D, 0);
}