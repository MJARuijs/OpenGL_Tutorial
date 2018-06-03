#pragma once

#include "Image.h"

class UserInterface {

private:
    std::vector<Image> images;

public:
    ~UserInterface() = default;

    void addImage(Image& image);

    void render(ShaderProgram& shaderProgram);
    void update(int width, int height);
    void cleanUp();
};
