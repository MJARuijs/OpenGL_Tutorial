#include "QuadMesh.h"

QuadMesh::QuadMesh(ShaderProgram &shaderProgram) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &tbo);

    textureCoords = { -1, 1, -1, -1, 1, 1, 1, -1 };

    shaderProgram.start();

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), &textureCoords[0], GL_STATIC_DRAW);
    shaderProgram.setAttribute(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    shaderProgram.stop();

}

QuadMesh::~QuadMesh() {
    glDeleteBuffers(1, &tbo);
    glDeleteVertexArrays(1, &vao);
    tbo = 0;
    vao = 0;
}

void QuadMesh::render() {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}
