#include "Renderer.h"
#include "../../Game.h"

Renderer::Renderer(const std::string& vertexPath, const std::string& fragmentPath)
        : shaderProgram(vertexPath, fragmentPath)
{}

void Renderer::addEntity(Entity& entity) {
    entities.push_back(entity);
}

void Renderer::prepareShadowRender(GLuint& shadowTextureId, const Mat4& shadowMatrix) {
    this->shadowTextureId = shadowTextureId;
    this->shadowMatrix = shadowMatrix;
}

void Renderer::render(Camera& camera) {
    shaderProgram.start();
    shaderProgram.set("ambient.color", ambient.color);
    shaderProgram.set("directional.color", sun.color);
    shaderProgram.set("directional.direction", sun.direction);
    shaderProgram.set("attenuation.constant", attenuation.constant);
    shaderProgram.set("attenuation.linear", attenuation.linear);
    shaderProgram.set("attenuation.quadratic", attenuation.quadratic);

    shaderProgram.set("projection", camera.projectionMatrix());
    shaderProgram.set("view", camera.viewMatrix());

    shaderProgram.set("shadowMatrix", shadowMatrix);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, shadowTextureId);
    shaderProgram.set("shadowMap", 0);

    for (Entity& entity : entities) {
        entity.render(shaderProgram);
    }

    shaderProgram.stop();
}

void Renderer::setAmbient(AmbientLight &ambient) {
    Renderer::ambient = ambient;
}

void Renderer::setSun(DirectionalLight &sun) {
    Renderer::sun = sun;
}

void Renderer::setAttenuation(Attenuation &attenuation) {
    Renderer::attenuation = attenuation;
}
