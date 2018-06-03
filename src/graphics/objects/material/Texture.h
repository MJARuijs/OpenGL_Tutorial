#pragma once
#include <GL/glew.h>
#include "TextureData.h"

class Texture {

private:
    GLuint id;

public:
    Texture(int index, int width, int height, unsigned char* data);
    Texture(TextureData* textureData);
    ~Texture() = default;

    int index;

    void bind();
    void unbind();
};

