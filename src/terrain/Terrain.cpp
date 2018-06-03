#include "Terrain.h"
#include "../loaders/ModelLoader.h"

Terrain::Terrain(ShaderProgram &shaderProgram, TerrainMesh *mesh) :
    mesh(mesh),
    transformation(1.0f)
{}

void Terrain::render(ShaderProgram& shaderProgram) {
    shaderProgram.set("model", transformation);
    mesh->render();
}

