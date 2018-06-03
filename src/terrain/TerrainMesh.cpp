#include "TerrainMesh.h"

TerrainMesh::TerrainMesh(ShaderProgram &shaderProgram,
                         std::vector<GLfloat> &vertices,
                         std::vector<GLfloat> &normals,
                         std::vector<GLfloat> &colors,
                         std::vector<GLuint> &indices) {

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &nbo);
    glGenBuffers(1, &colorBuffer);
    glGenBuffers(1, &ebo);

    shaderProgram.start();

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
    shaderProgram.setAttribute(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, nbo);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals[0], GL_STATIC_DRAW);
    shaderProgram.setAttribute(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), &colors[0], GL_STATIC_DRAW);
    shaderProgram.setAttribute(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLfloat), &indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    shaderProgram.stop();

    count = static_cast<GLsizei>(indices.size());
}

TerrainMesh::~TerrainMesh() {
    glDeleteBuffers(1, &ebo);
    ebo = 0;

    glDeleteBuffers(1, &vbo);
    vbo = 0;

    glDeleteBuffers(1, &nbo);
    nbo = 0;

    glDeleteVertexArrays(1, &vao);
    vao = 0;
}

void TerrainMesh::render() {
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}
