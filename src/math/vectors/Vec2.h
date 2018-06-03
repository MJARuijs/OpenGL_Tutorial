#pragma once

class Vec2 {

public:
    float values[2];

    Vec2(float x, float y);
    Vec2(float value);
    Vec2();

    float dot(Vec2& other);
    float length();
    void normalize();

    float& operator[] (int index);
    Vec2 operator* (float scale);
    Vec2 operator+ (Vec2& other);
    Vec2 operator+= (Vec2& other);
};
