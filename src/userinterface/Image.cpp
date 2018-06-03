#include <iostream>
#include "Image.h"

#define ALIGN_TOP_LEFT  0
#define ALIGN_BOTTOM_LEFT 1
#define ALIGN_TOP_RIGHT  2
#define ALIGN_BOTTOM_RIGHT 3

Image::Image(Mesh* mesh) :
        mesh(mesh),
        textured(false),
        translation(1.0f, 1.0f),
        scale(1.0f, 1.0f),
        depthTexture(false)
{}

Image::Image(Mesh* mesh, Texture *texture) :
        mesh(mesh),
        texture(texture),
        textured(true),
        translation(1.0f, 1.0f),
        scale(1.0f, 1.0f)
{}

Image::Image(Mesh* mesh, GLuint& textureID) :
        mesh(mesh),
        textureId(textureID),
        textured(false),
        translation(1.0f, 1.0f),
        scale(1.0f, 1.0f)
{}

void Image::update(int width, int height) {
    switch (alignmentType) {
        case ALIGN_TOP_LEFT:
            alignFromTopLeft(width, height);
            break;
        case ALIGN_BOTTOM_LEFT:
            alignFromBottomLeft(width, height);
            break;
        case ALIGN_TOP_RIGHT:
            alignFromTopRight(width, height);
            break;
        case ALIGN_BOTTOM_RIGHT:
            alignFromBottomRight(width, height);
            break;
        default:
            throw std::runtime_error("Invalid alignment type: " + alignmentType);
    }
}

void Image::render(ShaderProgram& shaderProgram) {
    shaderProgram.set("translation", position);
    shaderProgram.set("scale", scale);
    shaderProgram.set("depthTexture", depthTexture);

    if (textured) {
        texture->bind();
        shaderProgram.set("sampler", 0);
        mesh->render();
        texture->unbind();
    } else if (textureId != 0) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureId);
        shaderProgram.set("sampler", 0);
        mesh->render();
        glBindTexture(GL_TEXTURE_2D, 0);
    } else {
        mesh->render();
    }
}

void Image::alignFromTopLeft(int width, int height) {
    float xOffset = scale.values[0] / 2.f;
    float yOffset = scale.values[1] / 2.f;
    float ratio = (float)width / (float) height;

    position.values[0] = translation.values[0] - (ratio - xOffset);
    position.values[1] = translation.values[1] + ((float)height / 2 - yOffset / 2) / (float)height;
}

void Image::alignFromBottomLeft(int width, int height) {
    float xOffset = scale.values[0] / 2.f;
    float yOffset = scale.values[1] / 2.f;
    float ratio = (float)width / (float) height;

    position.values[0] = translation.values[0] - (ratio - xOffset);
    position.values[1] = translation.values[1] - ((float)height / 2 - yOffset) / (float)height;
}

void Image::alignFromTopRight(int width, int height) {
    float xOffset = scale.values[0] / 2.f;
    float yOffset = scale.values[1] / 2.f;
    float ratio = (float)width / (float) height;

    position.values[0] = translation.values[0] + (ratio - xOffset);
    position.values[1] = translation.values[1] + ((float)height / 2 - yOffset / 2) / (float)height;
}

void Image::alignFromBottomRight(int width, int height) {
    float xOffset = scale.values[0] / 2.f;
    float yOffset = scale.values[1] / 2.f;
    float ratio = (float)width / (float) height;

    position.values[0] = translation.values[0] + (ratio - xOffset);
    position.values[1] = translation.values[1] - ((float)height / 2 - yOffset / 2) / (float)height;
}

void Image::destroy() {
    if (textured) {
        delete texture;
    }
}
