#include <cmath>
#include "Mat4.h"

Mat4::Mat4(float matrix[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->matrix[i][j] = matrix[i][j];
        }
    }
}

Mat4::Mat4(float scale) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                matrix[i][j] = scale;
            } else {
                matrix[i][j] = 0.f;
            }
        }
    }
}

Mat4::Mat4() : Mat4(1.f) {}

void Mat4::setIdentity() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                matrix[i][j] = 1.f;
            } else {
                matrix[i][j] = 0.f;
            }
        }
    }
}

Mat4 Mat4::place(Vec3 position) {
    matrix[0][3] = position[0];
    matrix[1][3] = position[1];
    matrix[2][3] = position[2];
    return *this;
}

Mat4 Mat4::translate(Vec3 translation) {
    Mat4 translationMatrix;
    translationMatrix.matrix[0][3] += translation[0];
    translationMatrix.matrix[1][3] += translation[1];
    translationMatrix.matrix[2][3] += translation[2];

    return translationMatrix * *this;
}

Mat4 Mat4::rotateX(float rotation) {
    Mat4 rotationMatrix;
    rotationMatrix.matrix[1][1] = cosf(rotation);
    rotationMatrix.matrix[1][2] = -sinf(rotation);
    rotationMatrix.matrix[2][1] = sinf(rotation);
    rotationMatrix.matrix[2][2] = cosf(rotation);

    return rotationMatrix * *this;
}

Mat4 Mat4::rotateY(float rotation) {
    Mat4 rotationMatrix;
    rotationMatrix.matrix[0][0] = cosf(rotation);
    rotationMatrix.matrix[0][2] = sinf(rotation);
    rotationMatrix.matrix[2][0] = -sinf(rotation);
    rotationMatrix.matrix[2][2] = cosf(rotation);

    return rotationMatrix * *this;
}

Mat4 Mat4::rotateZ(float rotation) {
    Mat4 rotationMatrix;
    rotationMatrix.matrix[0][0] = cosf(rotation);
    rotationMatrix.matrix[0][1] = -sinf(rotation);
    rotationMatrix.matrix[1][0] = sinf(rotation);
    rotationMatrix.matrix[1][1] = cosf(rotation);

    return rotationMatrix * *this;
}

void Mat4::translate(Vec3 translation, Mat4& destination) {
    destination.matrix[0][3] += translation[0];
    destination.matrix[1][3] += translation[1];
    destination.matrix[2][3] += translation[2];
}

void Mat4::rotateX(float rotation, Mat4 &destination) {
    destination.matrix[1][1] = cosf(rotation);
    destination.matrix[1][2] = -sinf(rotation);
    destination.matrix[2][1] = sinf(rotation);
    destination.matrix[2][2] = cosf(rotation);
}

void Mat4::rotateY(float rotation, Mat4 &destination) {
    destination.matrix[0][0] = cosf(rotation);
    destination.matrix[0][2] = sinf(rotation);
    destination.matrix[2][0] = -sinf(rotation);
    destination.matrix[2][2] = cosf(rotation);
}

void Mat4::rotateZ(float rotation, Mat4 &destination) {
    destination.matrix[0][0] = cosf(rotation);
    destination.matrix[0][1] = -sinf(rotation);
    destination.matrix[1][0] = sinf(rotation);
    destination.matrix[1][1] = cosf(rotation);
}

Vec4 Mat4::operator*(Vec4 vector) {
    Vec4 result;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.values[i] += matrix[i][j] * vector[j];
        }
    }

    return result;
}

Mat4 Mat4::operator*(float scale) {
    Mat4 result(matrix);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.matrix[i][j] *= scale;

        }
    }
    return result;
}

Mat4 Mat4::operator*(Mat4 other) {
    Mat4 result(0.f);

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            for (int i = 0; i < 4; i++) {
                result.matrix[row][col] += matrix[row][i] * other.matrix[i][col];
            }
        }
    }

    return result;
}

Mat4 Mat4::operator*=(Mat4 &other) {
    Mat4 result = *this * other;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = result.matrix[i][j];
        }
    }
    return *this;
}

void Mat4::println() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

