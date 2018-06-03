#pragma once

#include <GL/glew.h>
#include <vector>
#include "../../graphics/shaders/ShaderProgram.h"

class WaterMesh {
private:
    GLuint vao;
    GLuint vbo;
    GLuint neighbourBuffer;
    GLuint ebo;
    GLsizei count;

public:
    WaterMesh(ShaderProgram &shaderProgram,
              std::vector<GLfloat> &vertices,
              std::vector<GLfloat> &neighbours,
              std::vector<GLuint> &indices);

    ~WaterMesh();

    void render();
};
