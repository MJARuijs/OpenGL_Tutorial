#include <cmath>
#include <iostream>
#include "Vec3.h"

Vec3::Vec3(float x, float y, float z) {
    values[0] = x;
    values[1] = y;
    values[2] = z;
}

Vec3::Vec3(float value) : Vec3(value, value, value) {}

Vec3::Vec3() : Vec3(0.0f, 0.0f, 0.0f) {}

float Vec3::dot(Vec3& other) {
    float result = 0.f;
    for (int i = 0; i < 3; i++) {
        result += values[i] * other[i];
    }
    return result;
}

Vec3 Vec3::cross(Vec3 other) {
    Vec3 result;
    result[0] = values[1] * other[2] - values[2] * other[1];
    result[1] = values[2] * other[0] - values[0] * other[2];
    result[2] = values[0] * other[1] - values[1] * other[0];
    return result;
}

float Vec3::length() {
    return sqrtf(values[0] * values[0] + values[1] * values[1] + values[2] * values[2]);
}

void Vec3::normalize() {
    float length = this->length();
    values[0] /= length;
    values[1] /= length;
    values[2] /= length;
}

Vec3 Vec3::getNormalized() {
    float length = this->length();
    float x = values[0] / length;
    float y = values[1] / length;
    float z = values[2] / length;
    return Vec3(x, y, z);
}

void Vec3::negate() {
    values[0] = -values[0];
    values[1] = -values[1];
    values[2] = -values[2];
}

Vec3 Vec3::getNegated() {
    return Vec3(-values[0], -values[1], -values[2]);
}

float& Vec3::operator[] (int index) {
    return values[index];
}

Vec3 Vec3::operator* (float scale) {
    return Vec3(values[0] * scale, values[1] * scale, values[2] * scale);
}

Vec3 Vec3::operator+ (Vec3 other) {
    Vec3 result;
    for (int i = 0; i < 3; i++) {
        result.values[i] = values[i] + other[i];
    }
    return result;
}

Vec3 Vec3::operator- (Vec3 other) {
    Vec3 result;
    for (int i = 0; i < 3; i++) {
        result.values[i] = values[i] - other[i];
    }
    return result;
}

Vec3 Vec3::operator+= (Vec3& other) {
    Vec3 result = *this + other;
    for (int i = 0; i < 3; i++) {
        values[i] = result[i];
    }
    return *this;
}

void Vec3::println() {
    std::cout << values[0] << ", " << values[1] << ", " << values[2] << std::endl;
}
