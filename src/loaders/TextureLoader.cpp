#include "TextureLoader.h"
#include "../graphics/objects/material/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::vector<TextureData> TextureLoader::textures;
//std::map<std::string, TextureData*> TextureLoader::textures;

Texture* TextureLoader::load(int type, const std::string& filePath) {

//    for (const auto &texture : textures) {
//        if (texture.first == filePath) {
//            return texture.second;
//        }
//    }

    int width;
    int height;
    int channels;
    unsigned char* data;

    data = stbi_load(filePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    if (!data) {
        throw std::runtime_error("Failed to load texture: " + std::string(stbi_failure_reason()));
    }

    auto * texture = new Texture(type, width, height, data);

//    stbi_image_free(data);

//    textures.emplace_back(type, width, height, data);
    return texture;
}

const TextureData& TextureLoader::loadData(int type, const std::string& filePath) {

    int width;
    int height;
    int channels;
    unsigned char* data;

    data = stbi_load(filePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    if (!data) {
        throw std::runtime_error("Failed to load texture: " + std::string(stbi_failure_reason()));
    }

    textures.emplace_back(type, width, height, data);
    return textures.back();
}

void TextureLoader::clear() {
    for (const auto &texture : textures) {
        stbi_image_free(texture.data);
    }
}


