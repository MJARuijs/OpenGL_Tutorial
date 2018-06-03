#pragma once

class Vec3 {

public:
    float values[3];

    Vec3(float x, float y, float z);
    Vec3(float value);
    Vec3();

    float dot(Vec3& other);
    Vec3 cross(Vec3 other);

    float length();
    void normalize();
    Vec3 getNormalized();

    Vec3 getNegated();
    void negate();

    float& operator[] (int index);
    Vec3 operator* (float scale);
    Vec3 operator+ (Vec3 other);
    Vec3 operator- (Vec3 other);
    Vec3 operator+= (Vec3& other);

    void println();
};
