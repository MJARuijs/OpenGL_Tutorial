#pragma once

#include "../shaders/ShaderProgram.h"
#include "../objects/Entity.h"
#include "../Lights.h"
#include "../Camera.h"

class Renderer {

private:
    AmbientLight ambient;
    DirectionalLight sun;
    Attenuation attenuation;

    GLuint shadowTextureId;
    Mat4 shadowMatrix;

public:
    Renderer(const std::string& vertexPath, const std::string& fragmentPath);
    ~Renderer() = default;

    void setAmbient(AmbientLight &ambient);
    void setSun(DirectionalLight &sun);
    void setAttenuation(Attenuation &attenuation);
    ShaderProgram shaderProgram;

    std::vector<Entity> entities;

    void addEntity(Entity& entity);

    void prepareShadowRender(GLuint& shadowTextureId, const Mat4& shadowMatrix);
    void render(Camera& camera);

};
