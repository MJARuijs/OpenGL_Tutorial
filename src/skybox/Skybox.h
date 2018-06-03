#pragma once

#include "../graphics/Camera.h"
#include "../graphics/shaders/ShaderProgram.h"
#include "SkyboxMesh.h"

class Skybox {

private:
    SkyboxMesh skyboxMesh;
    GLuint textureID;

public:
    Skybox(SkyboxMesh& skyboxMesh, std::vector<std::string>& textures);

    float rotation;

    void render();
    Mat4 getTransformation(float rotation);
};
