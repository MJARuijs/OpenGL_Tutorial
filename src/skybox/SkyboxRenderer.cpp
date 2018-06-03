#include <cmath>
#include "SkyboxRenderer.h"

SkyboxRenderer::SkyboxRenderer(const std::string &vertexPath, const std::string &fragmentPath, float skyboxDistance) :
        shaderProgram(vertexPath, fragmentPath)
{
    shaderProgram.start();
    shaderProgram.set("distance", skyboxDistance);
    shaderProgram.stop();
}

void SkyboxRenderer::setRotation(float rotation) {
    this->rotation = rotation;
}

Vec3 SkyboxRenderer::render(Camera &camera, Vec4 waterPlane) {
    shaderProgram.start();

    shaderProgram.set("cubeMap", 0);
    shaderProgram.set("view", camera.viewMatrix());
    shaderProgram.set("projection", camera.projectionMatrix());
    shaderProgram.set("waterPlane", waterPlane);

    for (Skybox& skybox : skyboxes) {
        shaderProgram.set("model", skybox.getTransformation(skybox.rotation));

        float skyboxRotation = rotation / ROTATION_SPEED;
        skybox.rotation += skyboxRotation;

        glDisable(GL_CULL_FACE);
        skybox.render();
        glEnable(GL_CULL_FACE);

        float scale = 800.f / 1024.f;

        float x = cosf((skybox.rotation + 0.58f)) * scale;
        float z = -sinf((skybox.rotation + 0.58f)) * scale;

        return Vec3(
                x * camera.skyboxDistance,
                camera.skyboxDistance,
                z * camera.skyboxDistance
        );
    }

    shaderProgram.stop();
}

void SkyboxRenderer::addSkybox(const Skybox& skybox) {
    skyboxes.push_back(skybox);
}
