#pragma once

#include "../graphics/objects/Mesh.h"
#include "../graphics/objects/material/Material.h"
#include "../graphics/objects/Entity.h"
#include "TerrainMesh.h"

class Terrain {

private:
    TerrainMesh* mesh;

public:
    Terrain(ShaderProgram& shaderProgram, TerrainMesh *mesh);
    ~Terrain() = default;

    Mat4 transformation;
    Vec3 scale;

    void render(ShaderProgram& shaderProgram);
};
