#include <cmath>
#include "ShadowRenderer.h"
#include "../../math/vectors/Vec2.h"

ShadowRenderer::ShadowRenderer(Camera& camera, int width, int height) :
        camera(camera),
        fbo(DEPTH_BUFFER, width, height),
        projectionMatrix(1.0f),
        lightViewMatrix(1.0f),
        shadowBox(camera)
{}

Mat4 ShadowRenderer::getShadowMatrix() {
    Mat4 matrix;
    matrix.matrix[0][0] = 0.5f;
    matrix.matrix[1][1] = 0.5f;
    matrix.matrix[2][2] = 0.5f;
    matrix.matrix[0][3] = 0.5f;
    matrix.matrix[1][3] = 0.5f;
    matrix.matrix[2][3] = 0.5f;
    return matrix * projectionMatrix * lightViewMatrix;
}

void ShadowRenderer::update(Camera& camera, Vec3 lightDirection) {
    this->camera = camera;
    shadowBox.update(camera, lightViewMatrix);

    fbo.bind();
    glClear(GL_DEPTH_BUFFER_BIT);
    updateProjectionMatrix(shadowBox.getWidth(), shadowBox.getHeight(), shadowBox.getDepth());
    updateLightViewMatrix(lightDirection, shadowBox.getCenter());
}

void ShadowRenderer::updateLightViewMatrix(Vec3 lightDirection, Vec3 center) {
    lightDirection.normalize();

    lightViewMatrix.setIdentity();
    Vec3 lightPosition = lightDirection;
    lightPosition.normalize();
    float xRotation = atanf(lightPosition[0] / lightPosition[2]);
    float yRotation = atanf(lightPosition[1] / lightPosition[0]);

    if (lightPosition[2] < 0) {
        xRotation -= (float)M_PI;
    }

    if (!(lightPosition[2] < 0 && yRotation < 0) && !(lightPosition[2] > 0 && yRotation > 0)) {
        yRotation *= -1;
    }

    lightViewMatrix = lightViewMatrix.rotateX(yRotation);
    lightViewMatrix = lightViewMatrix.rotateY(-xRotation);
    lightViewMatrix = lightViewMatrix.translate(lightDirection);
}

void ShadowRenderer::updateProjectionMatrix(float width, float height, float depth) {
    projectionMatrix.setIdentity();
    projectionMatrix.matrix[0][0] = 2.0f / width;
    projectionMatrix.matrix[1][1] = 2.0f / height;
    projectionMatrix.matrix[2][2] = -2.0f / depth;
    projectionMatrix.matrix[3][3] = 1.0f;
}

void ShadowRenderer::finish(int width, int height) {
    fbo.unbind(width, height);
}
