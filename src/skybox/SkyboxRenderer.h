#pragma once

#include "../graphics/shaders/ShaderProgram.h"
#include "../graphics/Camera.h"
#include "../graphics/Lights.h"
#include "Skybox.h"

class SkyboxRenderer {

private:
    float rotation;
    const float ROTATION_SPEED = 40.f;
    std::vector<Skybox> skyboxes;

public:
    SkyboxRenderer(const std::string& vertexPath, const std::string& fragmentPath, float skyboxDistance);
    ~SkyboxRenderer() = default;

    ShaderProgram shaderProgram;

    void addSkybox(const Skybox& skybox);
    void setRotation(float rotation);

    Vec3 render(Camera &camera, Vec4 waterPlane);
};
