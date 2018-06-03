#include <cmath>
#include "WaterGenerator.h"

int WaterGenerator::smoothness = 10;

WaterMesh *WaterGenerator::generate(ShaderProgram &shaderProgram, int size) {
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> neighbours;
    std::vector<GLuint> indices;

    std::vector<Vec3> points;

    float height = 0;
    int index = 0;
    for (int z = 0; z < size - 1; z++) {
        for (int x = 0; x < size - 1; x++) {
            generateSquare(x * smoothness, height, z * smoothness, index, points, indices, neighbours);
            index += 6;
        }
    }

    for (Vec3 point : points) {
        vertices.emplace_back(point[0]);
        vertices.emplace_back(point[1]);
        vertices.emplace_back(point[2]);
    }

    return new WaterMesh(shaderProgram, vertices, neighbours, indices);
}

void WaterGenerator::generateSquare(int x, float y, int z, int index, std::vector<Vec3> &points, std::vector<GLuint> &indices, std::vector<GLfloat> &neighbours) {
    Vec3 pointA(x, y, z);
    Vec3 pointB(x, y, z + smoothness);
    Vec3 pointC(x + smoothness, y, z + smoothness);
    Vec3 pointD(x + smoothness, y, z);

    points.emplace_back(pointC);
    points.emplace_back(pointA);
    points.emplace_back(pointB);

    points.emplace_back(pointA);
    points.emplace_back(pointC);
    points.emplace_back(pointD);

    addNeighbours(pointA, pointB, pointC, neighbours);
    addNeighbours(pointB, pointC, pointA, neighbours);
    addNeighbours(pointC, pointA, pointB, neighbours);

    addNeighbours(pointD, pointA, pointC, neighbours);
    addNeighbours(pointA, pointC, pointD, neighbours);
    addNeighbours(pointC, pointD, pointA, neighbours);

    indices.emplace_back(index);
    indices.emplace_back(index + 1);
    indices.emplace_back(index + 2);

    indices.emplace_back(index + 3);
    indices.emplace_back(index + 4);
    indices.emplace_back(index + 5);
}

void WaterGenerator::addNeighbours(Vec3 &a, Vec3 &b, Vec3 &c, std::vector<GLfloat> &neighbours) {
    Vec3 v1 = b - a;
    Vec3 v2 = c - a;
    neighbours.emplace_back(v1[0]);
    neighbours.emplace_back(v1[2]);
    neighbours.emplace_back(v2[0]);
    neighbours.emplace_back(v2[2]);
}

