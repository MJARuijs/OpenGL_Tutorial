#pragma once

#include <iostream>
#include "../vectors/Vec4.h"
#include "../vectors/Vec3.h"

class Mat4 {

public:
    float matrix[4][4];

    Mat4(float matrix[4][4]);
    Mat4(float scale);
    Mat4();

    void setIdentity();

    Mat4 place(Vec3 position);
    Mat4 translate(Vec3 translation);

    Mat4 rotateX(float rotation);
    Mat4 rotateY(float rotation);
    Mat4 rotateZ(float rotation);

    Vec4 operator*(Vec4 vector);
    Mat4 operator*(float scale);
    Mat4 operator*(Mat4 other);
    Mat4 operator*=(Mat4& other);

    void println();

    void translate(Vec3 translation, Mat4& destination);
    void rotateX(float rotation, Mat4& destination);
    void rotateY(float rotation, Mat4& destination);
    void rotateZ(float rotation, Mat4& destination);

};
