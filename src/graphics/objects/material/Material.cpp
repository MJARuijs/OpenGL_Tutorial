#include "Material.h"

Material::Material(Texture* texture, Color diffuseColor, Color specularColor, float shininess, float intensity) :
        texture(texture),
        textured(true),
        specularColor(specularColor),
        diffuseColor(diffuseColor),
        shininess(shininess),
        intensity(intensity)
{}

Material::Material(Color diffuseColor, Color specularColor, float shininess, float intensity) :
        textured(false),
        diffuseColor(diffuseColor),
        specularColor(specularColor),
        shininess(shininess),
        intensity(intensity)
{}
