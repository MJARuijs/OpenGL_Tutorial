#pragma once

#include <GL/glew.h>
#include "Mesh.h"
#include "material/Material.h"
#include "../../loaders/ModelLoader.h"

class Entity {

public:
    Entity(ShaderProgram& shaderProgram, const std::string &filePath, Material& material);
    Entity(ShaderProgram& shaderProgram, Mesh* mesh, Material& material);

    ~Entity() = default;
    Mesh* mesh;

    Vec3 scaling;
    Mat4 transformation;
    Material material;

    void translate(Vec3 translation);
    void rotate(Vec3 rotation);
    void scale(float scale);
    void render(ShaderProgram& shaderProgram);

    void place(Vec3 position);
};


