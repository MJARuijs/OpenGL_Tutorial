#pragma once

#include <stdexcept>
#include <glfw3.h>

class GLFW {

public:
    GLFW() {
        auto initialized = static_cast<bool>(glfwInit());

        if (!initialized) {
            throw std::runtime_error("Failed to initialize GLFW");
        }
    }

    ~GLFW() {
        glfwTerminate();
    }

    void poll() {
        glfwPollEvents();
    }
};
