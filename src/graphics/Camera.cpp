#include <cmath>
#include "Camera.h"

Camera::Camera(float fieldOfView, float nearPlane, float farPlane, float aspectRatio) :
    fov(fieldOfView),
    zNear(nearPlane),
    zFar(farPlane),
    aspectRatio(aspectRatio),
    skyboxDistance(sqrtf((farPlane * farPlane) / 3.f)),
    position(0.f),
    rotation(0.f)
{}

void Camera::setAspectRatio(float ratio) {
    aspectRatio = ratio;
}

float Camera::getAspectRatio() {
    return aspectRatio;
}

void Camera::update(Vec3& translation, Vec3& newRotation) {

    translation.negate();
    Vec4 cameraTranslation = Vec4(translation[0], translation[1], translation[2], 1.f);
    Vec4 cameraRotation = rotationMatrix() * cameraTranslation;

    position[0] += cameraRotation[0];
    position[1] += cameraRotation[1];
    position[2] += cameraRotation[2];

    float cosY = cosf(newRotation.values[1]);

    rotation[0] += newRotation.values[0] * cosY;
    rotation[1] += sinf(newRotation.values[1]);
}

Mat4 Camera::rotationMatrix() {
    Mat4 rotationMatrix;
    rotationMatrix = rotationMatrix.rotateX(rotation[0]);
    rotationMatrix = rotationMatrix.rotateY(-rotation[1]);

//    rotationMatrix.rotateX(rotation[0], rotationMatrix);
//    rotationMatrix.rotateY(-rotation[1], rotationMatrix);
    return rotationMatrix;
}

Mat4 Camera::projectionMatrix() {
    Mat4 perspective;
    perspective.matrix[0][0] = 1 / (aspectRatio * tanf(fov / 2.f));
    perspective.matrix[1][1] = 1 / tanf(fov / 2.f);
    perspective.matrix[2][2] = -(zFar + zNear) / (zFar - zNear);
    perspective.matrix[2][3] = -(2.f * zFar * zNear) / (zFar - zNear);
    perspective.matrix[3][2] = -1.f;
    perspective.matrix[3][3] = 0.f;
    return perspective;
}

Mat4 Camera::viewMatrix() {
    Mat4 viewMatrix;
    viewMatrix = viewMatrix.translate(position.getNegated());
//    viewMatrix.translate(position.getNegated(), viewMatrix);
    viewMatrix = viewMatrix.rotateY(rotation[1]);
    viewMatrix = viewMatrix.rotateX(rotation[0]);
    return viewMatrix;
}
