#pragma once

#include <GL/glew.h>
#include <vector>
#include "../graphics/shaders/ShaderProgram.h"

class TerrainMesh {

private:
    GLuint vao;
    GLuint vbo;
    GLuint nbo;
    GLuint colorBuffer;
    GLuint ebo;
    GLsizei count;

public:
    TerrainMesh(ShaderProgram &shaderProgram,
                std::vector<GLfloat> &vertices,
                std::vector<GLfloat> &normals,
                std::vector<GLfloat> &colors,
                std::vector<GLuint> &indices);

    ~TerrainMesh();

    void render();
};
