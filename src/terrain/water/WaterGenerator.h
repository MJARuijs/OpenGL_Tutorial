#pragma once

#include "WaterMesh.h"
#include "../../graphics/shaders/ShaderProgram.h"

class WaterGenerator {

private:
    static int smoothness;

    static void addNeighbours(Vec3 &a, Vec3 &b, Vec3 &c, std::vector<GLfloat> &neighbours);
    static void generateSquare(int x, float y, int z, int index, std::vector<Vec3> &points, std::vector<GLuint> &indices, std::vector<GLfloat> &neighbours);

public:
    static WaterMesh* generate(ShaderProgram &shaderProgram, int size);
};
