#include "WaterRenderer.h"
#include "../../components/peripherals/Window.h"

WaterRenderer::WaterRenderer() :
    shaderProgram("res/shaders/world/low_poly/water_vertex.glsl", "res/shaders/world/low_poly/water_fragment.glsl")
{
    dudvMap = TextureLoader::load(2, "res/textures/water/dudvMap.png");
    normalMap = TextureLoader::load(3, "res/textures/water/normalMap.png");
}

void WaterRenderer::addWaterTile(Water& water) {
    waterTiles.push_back(water);
}

void WaterRenderer::prepare(Camera &camera,
                            Renderer& entityRenderer,
                            TerrainRenderer &terrainRenderer,
                            SkyboxRenderer &skyboxRenderer, DirectionalLight& sun) {

    shaderProgram.start();
    shaderProgram.set("projection", camera.projectionMatrix());
    shaderProgram.set("view", camera.viewMatrix());
    shaderProgram.set("reflectionTexture", 0);
    shaderProgram.set("refractionTexture", 1);
    shaderProgram.set("dudvMap", 2);
    shaderProgram.set("normalMap", 3);
    shaderProgram.set("depthTexture", 4);
    shaderProgram.set("cameraPosition", camera.position);
    shaderProgram.set("sun.color", sun.color);
    shaderProgram.set("sun.direction", sun.direction);

    dudvMap->bind();
    normalMap->bind();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (Water& water : waterTiles) {

        glEnable(GL_CLIP_DISTANCE0);

        water.reflectionFbo.bind();
        water.reflectionFbo.clear();

        float distance = 2 * (camera.position[1] - water.getHeight());
        camera.position[1] -= distance;
        camera.rotation[0] = -camera.rotation[0];
        entityRenderer.render(camera);

        terrainRenderer.render(camera, Vec4(0, 1, 0, -water.getHeight() + 0.1f));
        skyboxRenderer.render(camera, Vec4(0, 1, 0, -water.getHeight() + 0.1f));

        water.refractionFbo.bind();
        water.refractionFbo.clear();

        camera.position[1] += distance;
        camera.rotation[0] = -camera.rotation[0];

        terrainRenderer.render(camera, Vec4(0, -1, 0, water.getHeight() + 0.1f));
        skyboxRenderer.render(camera, Vec4(0, -1, 0, water.getHeight() + 0.1f));

        water.refractionFbo.unbind(Window::getWidth(), Window::getHeight());
    }

}

void WaterRenderer::render(Camera &camera, float delta) {

    for (Water& water : waterTiles) {

        glDisable(GL_CLIP_DISTANCE0);

        shaderProgram.start();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, water.reflectionFbo.textureId);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, water.refractionFbo.textureId);

        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, water.refractionFbo.depthTextureId);

        if (wireFrameEnabled) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            water.render(shaderProgram, delta);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        } else {
            water.render(shaderProgram, delta);
        }

    }

    glDisable(GL_BLEND);
    dudvMap->unbind();
    normalMap->unbind();
    shaderProgram.stop();
}

void WaterRenderer::setWireFrame(bool wireFrameEnabled) {
    this->wireFrameEnabled = wireFrameEnabled;
}
