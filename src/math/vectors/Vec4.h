#pragma once

#include "Vec3.h"
#include "Vec2.h"

class Vec4 {

public:
    float values[4];

    Vec4(float x, float y, float z, float w);
    Vec4(Vec3 vector, float w);
    Vec4(Vec2 vector, float z, float w);
    Vec4(const float values[4]);
    Vec4(float value);
    Vec4();

    Vec3 xyz();

    float dot(Vec4& other);
    float length();
    void normalize();

    float& operator[] (int index);
    Vec4 operator* (float scale);
    Vec4 operator+ (Vec4& other);
    Vec4 operator+= (Vec4& other);

    void println();
};
