#pragma once

#include <set>
#include <glfw3.h>
#include "../../../math/vectors/Vec2.h"

class Mouse {

public:
    Mouse();
    ~Mouse() = default;

    bool captured = false;

    std::set<int> buttonsPressed;
    std::set<int> buttonsDown;
    std::set<int> buttonsReleased;

    Vec2 cursorPosition;

    void capture();
    void release();
    void toggle();
    void update(float& centerX, float& centerY);

    void onButtonPressed(int button, int action);
    void onCursorUpdate(double x, double y);

    static void button_callback(GLFWwindow* window, int button, int action, int mods);
    static void cursor_callback(GLFWwindow* window, double x, double y);
};

