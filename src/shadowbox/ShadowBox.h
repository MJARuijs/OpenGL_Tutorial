#pragma once

#include <vector>
#include "../math/vectors/Vec3.h"
#include "ShadowFrameBuffer.h"
#include "../math/matrices/Mat4.h"
#include "../graphics/Camera.h"

class ShadowBox {

private:
    const int SHADOW_DISTANCE = 20;

    float farWidth, farHeight, nearWidth, nearHeight;
    float minX, maxX, minY, maxY, minZ, maxZ;

    Mat4 lightViewMatrix;
    Camera camera;

    std::vector<Vec4> calculateFrustumVertices(Mat4 rotation, Vec3 forwardVector, Vec3 centerNear, Vec3 centerFar);
    Vec4 calculateFrustumCorner(Vec3 startPoint, Vec3 direction, float width);
    void calculateDimensions(Camera& camera);

public:
    ShadowBox(Camera& camera);
    ~ShadowBox() = default;

    Vec3 getCenter();
    float getHeight();
    float getWidth();
    float getDepth();

    void update(Camera& camera, Mat4& lightViewMatrix);

};
