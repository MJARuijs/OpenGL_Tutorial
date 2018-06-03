#pragma once

#include <vector>
#include <GL/glew.h>
#include "../shaders/ShaderProgram.h"

class Mesh {

private:
    GLuint vao;
    GLuint vbo;
    GLuint nbo;
    GLuint tbo;
    GLuint ebo;
    GLsizei count;

public:
    Mesh(ShaderProgram& shaderProgram,
         std::vector<GLfloat>& vertices,
         std::vector<GLfloat>& normals,
         std::vector<GLfloat>& textureCoords,
         std::vector<GLuint>& indices);

    ~Mesh();

    void render();
};

