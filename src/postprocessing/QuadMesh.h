#pragma once

#include <GL/glew.h>
#include <vector>
#include "../graphics/shaders/ShaderProgram.h"

class QuadMesh {

private:
    std::vector<GLfloat> textureCoords;
    GLuint vao;
    GLuint tbo;

public:
    QuadMesh(ShaderProgram& shaderProgram);
    ~QuadMesh();

    void render();
};
