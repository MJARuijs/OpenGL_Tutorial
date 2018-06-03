#include <cmath>
#include "Vec2.h"

Vec2::Vec2(float x, float y) {
    values[0] = x;
    values[1] = y;
}

Vec2::Vec2(float value) : Vec2(value, value) {}

Vec2::Vec2() : Vec2(0.0f, 0.0f) {}

float Vec2::dot(Vec2& other) {
    float result = 0.f;
    for (int i = 0; i < 2; i++) {
        result += values[i] * other[i];
    }
    return result;
}

float Vec2::length() {
    return sqrtf(values[0] * values[0] + values[1] * values[1]);
}

void Vec2::normalize() {
    float length = this->length();
    values[0] /= length;
    values[1] /= length;
}

float& Vec2::operator[] (int index) {
    return values[index];
}

Vec2 Vec2::operator* (float scale) {
    return Vec2(values[0] * scale, values[1] * scale);
}

Vec2 Vec2::operator+ (Vec2& other) {
    Vec2 result;
    for (int i = 0; i < 2; i++) {
        result.values[i] = values[i] + values[i];
    }
    return result;
}

Vec2 Vec2::operator+= (Vec2& other) {
    Vec2 result = *this + other;
    for (int i = 0; i < 2; i++) {
        values[i] = values[i];
    }
    return *this;
}
