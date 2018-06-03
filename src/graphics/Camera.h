#pragma once

#include "../math/matrices/Mat4.h"

// TODO: Make the Camera able to follow the Player in first or third person, or to detach and move freely through the world
class Camera {

private:
    float aspectRatio;

public:
    float skyboxDistance;

    Vec3 position;
    Vec3 rotation;

    Camera(float fieldOfView, float nearPlane, float farPlane, float aspectRatio);
    ~Camera() = default;

    void setAspectRatio(float ratio);
    void update(Vec3& translation, Vec3& newRotation);

    float getAspectRatio();

    Mat4 rotationMatrix();
    Mat4 projectionMatrix();
    Mat4 viewMatrix();

    float zNear;
    float zFar;
    float fov;
};

