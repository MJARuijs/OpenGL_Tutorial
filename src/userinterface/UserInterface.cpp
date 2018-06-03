#include "UserInterface.h"

void UserInterface::addImage(Image& image) {
    images.push_back(image);
}

void UserInterface::render(ShaderProgram& shaderProgram) {
    for (Image& image : images) {
        image.render(shaderProgram);
    }
}

void UserInterface::update(int width, int height) {
    for (Image& image : images) {
        image.update(width, height);
    }
}

void UserInterface::cleanUp() {
    for (Image& image : images) {
        image.destroy();
    }
}

