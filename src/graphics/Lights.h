#pragma once

#include "../math/vectors/Vec3.h"

struct AmbientLight {
    Vec3 color;
};

struct DirectionalLight {
    Vec3 color;
    Vec3 direction;
};

struct PointLight {
    Vec3 color;
    Vec3 position;
};

struct Attenuation {
    float constant = 1.0f;
    float linear = 1.0f;
    float quadratic = 1.0f;
};