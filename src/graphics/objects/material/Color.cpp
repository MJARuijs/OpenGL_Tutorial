#include "Color.h"

Color::Color(float r, float g, float b, bool convert) {
    if (convert) {
        r /= 255.0f;
        g /= 255.0f;
        b /= 255.0f;
    }

    this->r = r;
    this->g = g;
    this->b = b;
}

Color::Color(float value, bool convert) : Color(value, value, value, convert) {}

Color::Color() : Color(1.0f, false) {}

Color Color::interpolateColors(Color color1, Color color2, float mixFactor) {
    float weight = 1 - mixFactor;
    float r = (weight * color1.r) + (mixFactor * color2.r);
    float g = (weight * color1.g) + (mixFactor * color2.g);
    float b = (weight * color1.b) + (mixFactor * color2.b);

    return Color(r, g, b, false);
}

float Color::getR() {
    return r;
}

float Color::getG() {
    return g;
}

float Color::getB() {
    return b;
}

Vec3 Color::toVector() {
    return Vec3(r, g, b);
}
