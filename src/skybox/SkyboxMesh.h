#pragma once

#include <GL/glew.h>
#include <vector>
#include "../graphics/shaders/ShaderProgram.h"

class SkyboxMesh {

private:

    GLuint vbo;
    GLuint ebo;

public:
    SkyboxMesh(ShaderProgram& shaderProgram, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
    ~SkyboxMesh();
    GLuint vao;
    GLsizei count;
    void render();
};
