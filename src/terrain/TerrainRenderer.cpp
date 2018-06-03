#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer(const std::string &vertexPath, const std::string &fragmentPath)
        : shaderProgram(vertexPath, fragmentPath)
{
    wireFrameEnabled = false;
}

void TerrainRenderer::addTerrain(Terrain &terrain) {
    terrains.push_back(terrain);
}

void TerrainRenderer::setAmbient(AmbientLight &ambient) {
    this->ambient = ambient;
}

void TerrainRenderer::setSun(DirectionalLight &sun) {
    this->sun = sun;
}

void TerrainRenderer::setAttenuation(Attenuation &attenuation) {
    this->attenuation = attenuation;
}

void TerrainRenderer::prepareShadowRender(GLuint &shadowTextureId, const Mat4 &shadowMatrix) {
    this->shadowTextureId = shadowTextureId;
    this->shadowMatrix = shadowMatrix;
}

void TerrainRenderer::render(Camera &camera, Vec4 waterPlane) {
    shaderProgram.start();
    shaderProgram.set("ambient.color", ambient.color);
    shaderProgram.set("directional.color", sun.color);
    shaderProgram.set("directional.direction", sun.direction);

    shaderProgram.set("projection", camera.projectionMatrix());
    shaderProgram.set("view", camera.viewMatrix());

//    shaderProgram.set("shadowMatrix", shadowMatrix);
    shaderProgram.set("waterPlane", waterPlane);

//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, shadowTextureId);
//    shaderProgram.set("shadowMap", 0);

    for (Terrain& terrain : terrains) {
        if (wireFrameEnabled) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            terrain.render(shaderProgram);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        } else {
            terrain.render(shaderProgram);
        }
    }

    shaderProgram.stop();
}
