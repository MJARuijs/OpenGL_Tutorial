#pragma once
#include <GL/glew.h>
#include <map>
#include <iostream>
#include <vector>
#include "../graphics/objects/material/TextureData.h"
#include "../graphics/objects/material/Texture.h"

class TextureLoader {

private:
    static std::vector<TextureData> textures;
public:
	static Texture* load(int type, const std::string& filePath);
    static const TextureData& loadData(int type, const std::string& filePath);
	static void clear();
};

