#pragma once

#include <GL/glew.h>
#include "../graphics/Lights.h"
#include "../math/matrices/Mat4.h"
#include "../graphics/shaders/ShaderProgram.h"
#include "Terrain.h"
#include "../graphics/Camera.h"

class TerrainRenderer {

private:
    AmbientLight ambient;
    DirectionalLight sun;
    Attenuation attenuation;

    GLuint shadowTextureId;
    Mat4 shadowMatrix;

    std::vector<Terrain> terrains;

public:
    TerrainRenderer(const std::string& vertexPath, const std::string& fragmentPath);
    ~TerrainRenderer() = default;

    ShaderProgram shaderProgram;
    bool wireFrameEnabled;

    void addTerrain(Terrain &terrain);

    void setAmbient(AmbientLight &ambient);
    void setSun(DirectionalLight &sun);
    void setAttenuation(Attenuation &attenuation);

    void prepareShadowRender(GLuint& shadowTextureId, const Mat4& shadowMatrix);
    void render(Camera& camera, Vec4 waterPlane);
};
