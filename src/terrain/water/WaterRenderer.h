#pragma once

#include "../../graphics/shaders/ShaderProgram.h"
#include "../../graphics/Camera.h"
#include "Water.h"
#include "../../graphics/objects/Entity.h"
#include "../../graphics/renderers/Renderer.h"
#include "../TerrainRenderer.h"
#include "../../skybox/SkyboxRenderer.h"

class WaterRenderer {

private:
    std::vector<Water> waterTiles;
    Texture* dudvMap;
    Texture* normalMap;
    bool wireFrameEnabled;
    DirectionalLight sun;

public:
    WaterRenderer();
    ~WaterRenderer() = default;

    ShaderProgram shaderProgram;

    void setWireFrame(bool wireFrameEnabled);

    void addWaterTile(Water& water);

    void prepare(Camera &camera,
                 Renderer& entityRenderer,
                 TerrainRenderer &terrainRenderer,
                 SkyboxRenderer &skyboxRenderer,
                 DirectionalLight &sun);

    void render(Camera& camera, float delta);
};
