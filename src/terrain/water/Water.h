#pragma once

#include "../../graphics/objects/Mesh.h"
#include "../../graphics/FBO.h"
#include "WaterMesh.h"

class Water {

private:
    WaterMesh* waterTile;
    Vec3 scale;
    Mat4 transformation;
    float height;
    float moveFactor;

    const float WAVE_SPEED = 0.3f;

public:
    Water(ShaderProgram &shaderProgram, WaterMesh* waterTile, Vec3 position);
    ~Water() = default;

    float getHeight();

    FBO reflectionFbo;
    FBO refractionFbo;

    void render(ShaderProgram &shaderProgram, float delta);
};
