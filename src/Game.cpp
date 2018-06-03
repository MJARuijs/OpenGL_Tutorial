#include "Game.h"
#include "loaders/TextureLoader.h"
#include "loaders/MaterialLoader.h"
#include "loaders/OBJLoader.h"
#include "graphics/FBO.h"
#include "math/matrices/Mat4.h"
#include "math/vectors/Vec3.h"
#include "loaders/SceneLoader.h"
#include "shadowbox/ShadowBox.h"
#include "graphics/renderers/ShadowRenderer.h"
#include "terrain/Terrain.h"
#include "terrain/water/Water.h"
#include "skybox/Skybox.h"
#include "terrain/TerrainGenerator.h"
#include "terrain/water/WaterGenerator.h"
#include "postprocessing/PostProcessor.h"
#include <cmath>
#include <vector>

Game::Game() :
        camera(70.f * ((float)M_PI / 180.f), 0.1f, 1000.0f, devices.window.aspectRatio()),
        renderer("res/shaders/entity_vertex.glsl", "res/shaders/entity_fragment.glsl"),
        terrainRenderer("res/shaders/world/low_poly/terrain_vertex.glsl", "res/shaders/world/low_poly/terrain_fragment.glsl"),
        skyboxRenderer("res/shaders/world/skybox_vertex.glsl", "res/shaders/world/skybox_fragment.glsl", camera.skyboxDistance),
        devices(this),
        shadowRenderer(camera, 2048, 2048)
{
    camera.position = Vec3(0, 5, 0);
    camera.rotation = Vec3(0, (float)M_PI, 0);
    cameraMode = true;
    slowMode = false;
    useMouse = true;
    wireFrameEnabled = false;
}

void Game::run() {
    ShaderProgram uiProgram("res/shaders/ui_vertex.glsl", "res/shaders/ui_fragment.glsl");
    ShaderProgram shadowProgram("res/shaders/shadow_vertex.glsl", "res/shaders/shadow_fragment.glsl");

    std::vector<std::string> skyboxTextures = {
            "res/textures/skybox/Sky/right.png",
            "res/textures/skybox/Sky/left.png",
            "res/textures/skybox/Sky/top.png",
            "res/textures/skybox/Sky/bottom.png",
            "res/textures/skybox/Sky/back.png",
            "res/textures/skybox/Sky/front.png"
    };

    WaterMesh *waterTile = WaterGenerator::generate(waterRenderer.shaderProgram, 60);
    Water water(waterRenderer.shaderProgram, waterTile, Vec3(0, -10, 0));
    waterRenderer.addWaterTile(water);

    std::vector<Color> biomeColors;

    // Water Terrain
//    biomeColors.emplace_back(201, 178, 99, true);
//    biomeColors.emplace_back(164, 155, 98, true);
//    biomeColors.emplace_back(229, 219, 164, true);
//    biomeColors.emplace_back(135, 184, 82, true);
//    biomeColors.emplace_back(80, 171, 93, true);
//    biomeColors.emplace_back(120, 120, 120, true);
//    biomeColors.emplace_back(200, 200, 210, true);

    // Planes terrain
    biomeColors.emplace_back(201, 178, 99, true);
    biomeColors.emplace_back(135, 184, 82, true);
    biomeColors.emplace_back(80, 171, 93, true);
    biomeColors.emplace_back(120, 120, 120, true);
    biomeColors.emplace_back(200, 200, 210, true);

    TerrainMesh *terrainMesh = TerrainGenerator::generateTerrain<40>(terrainRenderer.shaderProgram, biomeColors);
    Terrain terrain(terrainRenderer.shaderProgram, terrainMesh);
    terrainRenderer.addTerrain(terrain);

    SkyboxMesh skyboxMesh(skyboxRenderer.shaderProgram, skyboxVertices, skyboxIndices);
    Skybox skybox(skyboxMesh, skyboxTextures);
    skyboxRenderer.addSkybox(skybox);

    std::vector<Entity> terrainEntities = SceneLoader::load(renderer.shaderProgram, "res/objects/water_island.dae");

    for (Entity& terrainEntity : terrainEntities) {
        terrainEntity.scaling = Vec3(30.f);
        terrainEntity.translate(Vec3(-4.8f, -4.8f, -5.f));
    }

    std::vector<Entity> duck = SceneLoader::load(renderer.shaderProgram, "res/objects/duck.dae");

    for (Entity &entity : duck) {
//        renderer.addEntity(entity);
    }

    Material material(Color(0.5f, false), Color(0.5f, false), 20.f, 0.5f);

    Entity sphere(renderer.shaderProgram, "res/objects/textured-sphere.obj", material);

    ambient.color = Vec3(0.25f);
    directional.color = Vec3(0.75f);
    directional.direction = Vec3(0.5625f * camera.skyboxDistance, camera.skyboxDistance, -0.415f * camera.skyboxDistance);

    pointLight1.color = Vec3(0.5f);
    pointLight1.position = Vec3(0.f, 0.f, 5.f);
    pointLight2.color = Vec3(0.5f);
    pointLight2.position = Vec3(0, 0, -6.f);

    attenuation.constant = 0.01f;
    attenuation.linear = 0.1f;
    attenuation.quadratic = 0.5f;

    renderer.setAmbient(ambient);
    renderer.setAttenuation(attenuation);

    renderer.addEntity(sphere);

    terrainRenderer.setAmbient(ambient);
    terrainRenderer.setAttenuation(attenuation);

    Texture* texture = TextureLoader::load(0, "res/textures/space.png");
    Mesh *quad = ModelLoader::load(uiProgram, "res/objects/quad.obj");
    Image image(quad, texture);
    image.scale = Vec2(0.5f, 0.5f);
    image.translation = Vec2(0.f, 0.f);
    image.depthTexture = false;
    image.alignmentType = ALIGN_TOP_LEFT;

//    Image image2(quad, water.refractionFbo.depthTextureId);
//    image2.scale = Vec2(0.5f, 0.5f);
//    image2.translation = Vec2(0.f, 0.f);
//    image2.depthTexture = false;
//    image2.alignmentType = ALIGN_TOP_RIGHT;

    userInterface.addImage(image);
//    userInterface.addImage(image2);
    userInterface.update(Window::getWidth(), Window::getHeight());

    devices.showWindow();

    while (!devices.window.isClosed()) {

        devices.update();
        glfw.poll();
        processInput();

        prepareRenderers();

        waterRenderer.render(camera, devices.timer.delta());
        terrainRenderer.render(camera, Vec4());
        renderer.render(camera);
        directional.direction = skyboxRenderer.render(camera, Vec4());

        postProcessor.applyEffects();
    }

    cleanUp();
}

void Game::prepareRenderers() {
    renderer.setSun(directional);
    renderer.prepareShadowRender(shadowRenderer.fbo.depthTextureId, shadowRenderer.getShadowMatrix());
    waterRenderer.setWireFrame(wireFrameEnabled);
    waterRenderer.prepare(camera, renderer, terrainRenderer, skyboxRenderer, directional);

    terrainRenderer.setSun(directional);
    terrainRenderer.prepareShadowRender(shadowRenderer.fbo.depthTextureId, shadowRenderer.getShadowMatrix());
    skyboxRenderer.setRotation(devices.timer.delta());

    postProcessor.prepare();
}

void Game::renderShadows(ShaderProgram &shadowProgram, ShaderProgram &entityProgram, Terrain& terrain) {
    shadowProgram.start();
    shadowRenderer.update(camera, directional.direction);
    shadowProgram.set("projection", shadowRenderer.projectionMatrix);
    shadowProgram.set("view", shadowRenderer.lightViewMatrix);
    shadowProgram.set("model", Mat4(1.0f));

    terrain.render(shadowProgram);

    shadowRenderer.finish(Window::getWidth(), Window::getHeight());
    shadowProgram.stop();
}

void Game::renderUserInterface(ShaderProgram &uiProgram) {
    uiProgram.start();
    uiProgram.set("aspectRatio", devices.window.aspectRatio());
    userInterface.render(uiProgram);
    uiProgram.stop();
}

void Game::processInput() {

    float deltaTime = devices.timer.delta();
    float movementSpeed;

    if (slowMode) {
        movementSpeed = 10.f;
    } else {
        movementSpeed = 60.f;
    }

    Vec3 cameraTranslation(0.f);
    Vec3 cameraRotation(0.f);

    if (devices.keyboard().keyPressed(GLFW_KEY_O)) {
        devices.window.toggleFullScreen();
    }
    if (devices.keyboard().keyPressed(GLFW_KEY_Z)) {
        wireFrameEnabled = !wireFrameEnabled;
    }
    if (devices.keyboard().keyPressed(GLFW_KEY_ESCAPE)) {
        devices.mouse().toggle();
    }
    if (devices.keyboard().keyPressed(GLFW_KEY_LEFT_CONTROL)) {
        slowMode = !slowMode;
    }
    if (!devices.mouse().captured) {
        return;
    }
    if (devices.keyboard().keyPressed(GLFW_KEY_C)) {
        useMouse = !useMouse;
    }
    if (devices.keyboard().keyPressed(GLFW_KEY_T)) {
        cameraMode = !cameraMode;
    }
    if (devices.keyboard().keyPressed(GLFW_KEY_R)) {
        Mat4 rotationMatrix;
        rotationMatrix = rotationMatrix.rotateY((float) M_PI_2);
        Vec3 rotatedLight = (rotationMatrix * Vec4(directional.direction, 1)).xyz();
        directional.direction = rotatedLight;
    }

    if (devices.keyboard().keyDown(GLFW_KEY_M)) {
        directional.direction = Vec3(0.f, 0.f, 10.f);
//        directional.direction = Vec3(0.5625f * camera.skyboxDistance, camera.skyboxDistance, -0.415f * camera.skyboxDistance);
    }

    if (devices.keyboard().keyDown(GLFW_KEY_N)) {
        directional.direction = Vec3(0.f, 0.f, -10.f);
//        directional.direction = Vec3(-0.5625f * camera.skyboxDistance, -camera.skyboxDistance, 0.415f * camera.skyboxDistance);
    }

    float cubex = 0.f;
    float cubey = 0.f;
    float cubez = 0.f;

    if (devices.keyboard().keyDown(GLFW_KEY_W)) {
        if (cameraMode) {
            cameraTranslation[2] += movementSpeed * deltaTime;
        } else {
            cubez += movementSpeed * deltaTime;
        }
    }
    if (devices.keyboard().keyDown(GLFW_KEY_S)) {
        if (cameraMode) {
            cameraTranslation[2] -= movementSpeed * deltaTime;
        } else {
            cubez -= movementSpeed * deltaTime;
        }
    }
    if (devices.keyboard().keyDown(GLFW_KEY_A)) {
        if (cameraMode) {
            cameraTranslation[0] += movementSpeed * deltaTime;
        } else {
            cubex += movementSpeed * deltaTime;
        }
    }
    if (devices.keyboard().keyDown(GLFW_KEY_D)) {
        if (cameraMode) {
            cameraTranslation[0] -= movementSpeed * deltaTime;
        } else {
            cubex -= movementSpeed * deltaTime, 0, 0;
        }
    }
    if (devices.keyboard().keyDown(GLFW_KEY_SPACE)) {
        if (cameraMode) {
            cameraTranslation[1] -= movementSpeed * deltaTime;
        } else {
            cubey += movementSpeed * deltaTime;
        }
    }
    if (devices.keyboard().keyDown(GLFW_KEY_LEFT_SHIFT)) {
        if (cameraMode) {
            cameraTranslation[1] += movementSpeed * deltaTime;
        } else {
            cubey -= movementSpeed * deltaTime;
        }
    }

//    cube.translate(Vec3(cubex, cubey, cubez));

    float scale = 25.f * deltaTime / 100.f;

    float x = 0.f;
    float y = 0.f;

    if (useMouse) {
        x = devices.mouse().cursorPosition[1] - Window::getHeight() / 2.0f;
        y = devices.mouse().cursorPosition[0] - Window::getWidth() / 2.f;
    } else {
        if (devices.keyboard().keyDown(GLFW_KEY_LEFT)) {
            y -= 5.9f;
        }
        if (devices.keyboard().keyDown(GLFW_KEY_RIGHT)) {
            y += 5.9f;
        }
        if (devices.keyboard().keyDown(GLFW_KEY_UP)) {
            x -= 5.9f;
        }
        if (devices.keyboard().keyDown(GLFW_KEY_DOWN)) {
            x += 5.9f;
        }
    }

    Vec2 cursorPosition(x, y);

    Vec2 rotation = cursorPosition * scale;
    cameraRotation[0] = remainder((cameraRotation[0] + rotation[0]), 2.f * (float)M_PI);
    cameraRotation[1] = remainder((cameraRotation[1] + rotation[1]), 2.f * (float)M_PI);

    camera.update(cameraTranslation, cameraRotation);
}

void Game::cleanUp() {
    userInterface.cleanUp();
    TextureLoader::clear();
}

void Game::onSizeChanged(int width, int height) {
    userInterface.update(width, height);
    camera.setAspectRatio(devices.window.aspectRatio());
}
