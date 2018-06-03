#include <stdexcept>

#include "../../Game.h"
#include "Window.h"

int Window::height = 720;
int Window::width = 1280;

Window::Window(const std::string& title, int width, int height, WindowSizeCallback * callback) : callback(callback) {
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    windowId = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (windowId == nullptr) {
        throw std::runtime_error("Failed to open GLFW windowId");
    }

    glfwMakeContextCurrent(windowId);
    glfwSwapInterval(1);

    fullScreen = false;
}

Window::~Window() {
    glfwDestroyWindow(windowId);
}

void Window::setBackgroundColor(float red, float green, float blue) {
    glClearColor(red, green, blue, 1.0f);
}

void Window::updateWindowSize() {
    int w;
    int h;

    glfwGetWindowSize(windowId, &w, &h);

    if (w != width || h != height) {
        width = w;
        height = h;
        callback->onSizeChanged(width, height);
    }
}

float Window::aspectRatio() {
    updateWindowSize();
    return ((float)width / (float)height);
}

void Window::toggleFullScreen() {
    if (fullScreen) {
        glfwSetWindowMonitor(windowId, nullptr,
                             static_cast<int>(oldWindowPosition[0]),
                             static_cast<int>(oldWindowPosition[1]),
                             static_cast<int>(oldWindowSize[0]),
                             static_cast<int>(oldWindowSize[1]), 0);

        fullScreen = false;
    } else {
        int posX, posY;
        int sizeX, sizeY;
        glfwGetWindowPos(windowId, &posX, &posY);
        glfwGetWindowSize(windowId, &sizeX, &sizeY);
        oldWindowPosition[0] = posX;
        oldWindowPosition[1] = posY;

        oldWindowSize[0] = sizeX;
        oldWindowSize[1] = sizeY;
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwSetWindowMonitor(windowId, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, 0);

        fullScreen = true;
    }


}

void Window::resize(int width, int height) {
    glViewport(0, 0, width, height);
}

bool Window::isClosed() {
    return static_cast<bool>(glfwWindowShouldClose(windowId));
}

void Window::update() {
    glfwSwapBuffers(windowId);
}

void Window::clear() {
    updateWindowSize();
    glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::show() {
    glfwFocusWindow(windowId);
    glfwShowWindow(windowId);
}

void Window::hide() {
    glfwHideWindow(windowId);
}

void Window::close() {
    glfwSetWindowShouldClose(windowId, true);
}

int Window::getWidth() {
    return width ;
}

int Window::getHeight() {
    return height;
}
