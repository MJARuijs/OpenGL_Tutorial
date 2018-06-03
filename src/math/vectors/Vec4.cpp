#include <cmath>
#include <iostream>
#include "Vec4.h"

Vec4::Vec4(float x, float y, float z, float w) {
    values[0] = x;
    values[1] = y;
    values[2] = z;
    values[3] = w;
}

Vec4::Vec4(Vec3 vector, float w) {
    values[0] = vector.values[0];
    values[1] = vector.values[1];
    values[2] = vector.values[2];
    values[3] = w;
}

Vec4::Vec4(Vec2 vector, float z, float w) {
    values[0] = vector.values[0];
    values[1] = vector.values[1];
    values[2] = z;
    values[3] = w;
}

Vec4::Vec4(const float *values) {
    this->values[0] = values[0];
    this->values[1] = values[1];
    this->values[2] = values[2];
    this->values[3] = values[3];
}

Vec4::Vec4(float value) : Vec4(value, value, value, value) {}

Vec4::Vec4() : Vec4(0.0f, 0.0f, 0.0f, 0.f) {}

Vec3 Vec4::xyz() {
    return Vec3(values[0], values[1], values[2]);
}

float Vec4::dot(Vec4& other) {
    float result = 0.f;
    for (int i = 0; i < 4; i++) {
        result += values[i] * other[i];
    }
    return result;
}

float Vec4::length() {
    return sqrtf(values[0] * values[0] + values[1] * values[1] + values[2] * values[2] + values[3] * values[3]);
}

void Vec4::normalize() {
    float length = this->length();
    values[0] /= length;
    values[1] /= length;
    values[2] /= length;
    values[3] /= length;
}

float& Vec4::operator[](int index) {
    return values[index];
}

Vec4 Vec4::operator*(float scale) {
    return Vec4(values[0] * scale, values[1] * scale, values[2] * scale, values[3] * scale);
}

Vec4 Vec4::operator+ (Vec4& other) {
    Vec4 result;
    for (int i = 0; i < 4; i++) {
        result.values[i] = values[i] + other[i];
    }
    return result;
}

Vec4 Vec4::operator+= (Vec4& other) {
    Vec4 result = *this + other;
    for (int i = 0; i < 4; i++) {
        values[i] = result[i];
    }
    return *this;
}

void Vec4::println() {
    std::cout << values[0] << ", " << values[1] << ", " << values[2] << ", " << values[3] << std::endl;
}
