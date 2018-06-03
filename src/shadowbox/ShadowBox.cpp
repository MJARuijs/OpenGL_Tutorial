#include <cmath>
#include "ShadowBox.h"
#include "../math/matrices/Mat4.h"
#include "../math/vectors/Vec2.h"

ShadowBox::ShadowBox(Camera& camera) : camera(camera) {
    lightViewMatrix.setIdentity();
    calculateDimensions(camera);
}

Vec3 ShadowBox::getCenter() {
    float x = (minX + maxX) / 2.f;
    float y = (minY + maxY) / 2.f;
    float z = (minZ + maxZ) / 2.f;

//    glm::mat4 mat(1.0f);
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 4; j++) {
//            mat[i][j] = lightViewMatrix.matrix[i][j];
//        }
//    }
//    glm::mat4 inverse = glm::inverse(mat);
//
//    Vec4 center(x, y, z, 1.f);
//
//    glm::tmat4x4<float> lightView(1.0f);
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 4; j++) {
//            lightView[i][j] = lightViewMatrix.matrix[i][j];
//        }
//    }
//
//    glm::inverse(lightView);
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 4; j++) {
//            lightViewMatrix.matrix[i][j] = lightView[i][j];
//        }
//    }
//    return Vec3((lightViewMatrix * center).xyz());
    return Vec3(x, y, z);
}

float ShadowBox::getHeight() {
    return maxX - minX;
}

float ShadowBox::getWidth() {
    return maxY - minY;
}

float ShadowBox::getDepth() {
    return maxZ - minZ;
}

void ShadowBox::update(Camera& camera, Mat4& lightViewMatrix) {
    Mat4 rotation = camera.rotationMatrix();

    Vec3 forwardVector((rotation * Vec4(0.f, 0.f, 1.f, 0.f)).xyz());
    Vec3 nearVector = forwardVector * camera.zNear;
    Vec3 farVector = forwardVector * SHADOW_DISTANCE;

    Vec3 centerNear = nearVector + camera.position;
    Vec3 centerFar = farVector + camera.position;

    std::vector<Vec4> vertices = calculateFrustumVertices(rotation, forwardVector, centerNear, centerFar);

    bool first = true;

    for (Vec4 point : vertices) {
        if (first) {
            first = false;
            minX = point[0];
            maxX = point[0];
            minY = point[1];
            maxY = point[1];
            minZ = point[2];
            maxZ = point[2];
            continue;
        }

        if (point[0] > maxX) {
            maxX = point[0];
        } else if (point[0] < minX) {
            minX = point[0];
        }

        if (point[1] > maxY) {
            maxY = point[1];
        } else if (point[1] < minY) {
            minY = point[1];
        }

        if (point[2] > maxZ) {
            maxZ = point[2];
        } else if (point[2] < minZ) {
            minZ = point[2];
        }
    }
}

Vec4 ShadowBox::calculateFrustumCorner(Vec3 startPoint, Vec3 direction, float width) {
    Vec3 point = startPoint + (Vec3(direction) * width);
    Vec4 result = lightViewMatrix * Vec4(point[0], point[1], point[2], 0.f);
    return result;
}

void ShadowBox::calculateDimensions(Camera& camera) {
    farWidth = SHADOW_DISTANCE * tanf(camera.fov);
    nearWidth = camera.zNear * tanf(camera.fov);
    farHeight = farWidth / camera.getAspectRatio();
    nearHeight = nearWidth / camera.getAspectRatio();
}

std::vector<Vec4> ShadowBox::calculateFrustumVertices(Mat4 rotation, Vec3 forwardVector, Vec3 centerNear, Vec3 centerFar) {
    std::vector<Vec4> vertices;

    Vec3 up((rotation * Vec4(0.f, 1.f, 0.f, 0.f)).xyz());
    Vec3 down(up.getNegated());

    Vec3 right(forwardVector.cross(up));
    Vec3 left(right.getNegated());

    Vec3 farTop = centerFar + up * farHeight;
    Vec3 farBottom = centerFar + down * farHeight;

    Vec3 nearTop = centerNear + up * nearHeight;
    Vec3 nearBottom = centerNear + down * nearHeight;

    vertices.push_back(calculateFrustumCorner(farTop, right, farWidth));
    vertices.push_back(calculateFrustumCorner(farTop, left, farWidth));
    vertices.push_back(calculateFrustumCorner(farBottom, right, farWidth));
    vertices.push_back(calculateFrustumCorner(farBottom, left, farWidth));

    vertices.push_back(calculateFrustumCorner(nearTop, right, nearWidth));
    vertices.push_back(calculateFrustumCorner(nearTop, left, nearWidth));
    vertices.push_back(calculateFrustumCorner(nearBottom, right, nearWidth));
    vertices.push_back(calculateFrustumCorner(nearBottom, left, nearWidth));

    return vertices;
}
