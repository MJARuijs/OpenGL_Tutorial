#pragma once

#include <GL/glew.h>
#include <stdexcept>

class Glew {

public:
    Glew() {
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) {
            throw std::runtime_error("Failed to initialize GLEW");
        }

        glEnable(GL_TEXTURE);
        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
    }

    ~Glew() = default;
};
