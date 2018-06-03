#pragma once

#include "../../../loaders/TextureLoader.h"
#include "../../../math/vectors/Vec3.h"
#include "Texture.h"
#include "Color.h"

class Material {

public:
    Material(Texture* texture, Color diffuseColor, Color specularColor, float shininess, float intensity);
    Material(Color diffuseColor, Color specularColor, float shininess, float intensity);
    ~Material() = default;

    Texture* texture;
    bool textured;
    Color specularColor;
    Color diffuseColor;
    float shininess;
    float intensity;
};

