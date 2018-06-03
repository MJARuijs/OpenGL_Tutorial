#pragma once

#include <GL/glew.h>
#include <vector>
#include "components/Glew.h"
#include "components/GLFW.h"
#include "components/peripherals/Devices.h"
#include "graphics/Camera.h"
#include "graphics/renderers/Renderer.h"
#include "userinterface/UserInterface.h"
#include "math/vectors/Vec3.h"
#include "graphics/renderers/ShadowRenderer.h"
#include "terrain/Terrain.h"
#include "terrain/water/WaterRenderer.h"
#include "graphics/Lights.h"
#include "terrain/TerrainRenderer.h"
#include "skybox/SkyboxRenderer.h"
#include "postprocessing/PostProcessor.h"

class Game : WindowSizeCallback {

private:
    GLFW glfw;
    Devices devices;
    Glew glew;
    Camera camera;

    Renderer renderer;
    ShadowRenderer shadowRenderer;
    WaterRenderer waterRenderer;
    TerrainRenderer terrainRenderer;
    SkyboxRenderer skyboxRenderer;

    AmbientLight ambient;
    DirectionalLight directional;
    PointLight pointLight1;
    PointLight pointLight2;
    Attenuation attenuation;
    UserInterface userInterface;

    PostProcessor postProcessor;

    bool cameraMode;
    bool slowMode;
    bool useMouse;
    bool wireFrameEnabled;

    void processInput();
    void renderShadows(ShaderProgram& shadowProgram, ShaderProgram &entityProgram, Terrain& terrain);
    void renderUserInterface(ShaderProgram& uiProgram);
    void onSizeChanged(int width, int height) override;

    void cleanUp();

public:
    Game();
    ~Game() = default;

    void run();
    void prepareRenderers();

    std::vector<GLfloat> skyboxVertices = {
            -1,  1,  1,
            -1, -1,  1,
            1, -1,  1,
            1,  1,  1,

            // Front
            -1,  1, -1,
            -1, -1, -1,
            1, -1, -1,
            1,  1, -1,

            // Right
            1,  1, -1,
            1, -1, -1,
            1, -1,  1,
            1,  1,  1,

            // Left
            -1,  1, -1,
            -1, -1, -1,
            -1, -1,  1,
            -1,  1,  1,

            // Bottom
            -1,  1,  1,
            -1,  1, -1,
            1,  1, -1,
            1,  1,  1,

            // Top
            -1, -1,  1,
            -1, -1, -1,
            1, -1, -1,
            1, -1,  1
    };

    std::vector<GLuint> skyboxIndices = {

            // Back
            0,  1, 2,
            0,  2, 3,

            // Front
            4,  6, 5,
            4,  7, 6,

            // Right
            8,  10,  9,
            8,  11, 10,

            // Left
            12, 13, 14,
            12, 14, 15,

            // Top
            16, 18, 17,
            16, 19, 18,

            // Bottom
            20, 21, 22,
            20, 22, 23
    };

};


