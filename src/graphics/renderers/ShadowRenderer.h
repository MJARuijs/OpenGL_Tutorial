#pragma once

#include "../../shadowbox/ShadowBox.h"
#include "../shaders/ShaderProgram.h"
#include "../objects/Entity.h"
#include "../FBO.h"

class ShadowRenderer {

private:
    ShadowBox shadowBox;

    Camera camera;

    void updateLightViewMatrix(Vec3 lightDirection, Vec3 center);
    void updateProjectionMatrix(float width, float height, float depth);

public:
    ShadowRenderer(Camera& camera, int width, int height);
    ~ShadowRenderer() = default;

    FBO fbo;

    Mat4 projectionMatrix;
    Mat4 lightViewMatrix;
    Mat4 getShadowMatrix();

    void update(Camera& camera, Vec3 lightDirection);
    void finish(int width, int height);
};
