#pragma once

#include <string>
#include <glfw3.h>
#include "../../math/vectors/Vec2.h"
#include "WindowSizeCallback.h"

class Window {

private:
    GLFWwindow* windowId;
    WindowSizeCallback* callback;
    static int width;
    static int height;
    bool fullScreen;
    Vec2 oldWindowPosition;
    Vec2 oldWindowSize;

public:
    Window(const std::string &title, int width, int height, WindowSizeCallback * callback);
    ~Window();

    void setBackgroundColor(float red, float green, float blue);
    bool isClosed();

    void update();
    void clear();

    static int getWidth();
    static int getHeight();

    void updateWindowSize();
    float aspectRatio();

    void toggleFullScreen();
    void resize(int width, int height);
    void show();
    void hide();
    void close();
};
