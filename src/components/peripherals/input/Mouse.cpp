#include "Mouse.h"
#include "Input.h"

Mouse::Mouse() : cursorPosition(1.0f, 1.0f) {
    capture();
}

void Mouse::capture() {
    GLFWwindow* window = glfwGetCurrentContext();
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    captured = true;
}

void Mouse::release() {
    GLFWwindow* window = glfwGetCurrentContext();
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    captured = false;
}

void Mouse::toggle() {
    if (captured) {
        release();
    } else {
        capture();
    }
}

void Mouse::update(float& centerX, float& centerY) {
    GLFWwindow* window = glfwGetCurrentContext();
    buttonsPressed.clear();

    if (captured) {
        cursorPosition.values[0] = centerX;
        cursorPosition.values[1] = centerY;
        glfwSetCursorPos(window, centerX, centerY);
    }
}

void Mouse::onButtonPressed(int button, int action) {
    switch (action) {
        case GLFW_PRESS:
            buttonsPressed.insert(button);
            break;
        case GLFW_RELEASE:
            buttonsReleased.insert(button);
            break;
    }
}

void Mouse::onCursorUpdate(double x, double y) {
    cursorPosition.values[0] = ((float)x);
    cursorPosition.values[1] = ((float)y);
}

void Mouse::button_callback(GLFWwindow* window, int button, int action, int mods) {
    void* data = glfwGetWindowUserPointer(window);
    auto * input = static_cast<Input*>(data);
    input->onButtonPressed(button, action);
}

void Mouse::cursor_callback(GLFWwindow* window, double x, double y) {
    void* data = glfwGetWindowUserPointer(window);
    auto * input = static_cast<Input*>(data);
    input->onCursorUpdate(x, y);
}