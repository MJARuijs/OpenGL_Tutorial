#include "Devices.h"

Devices::Devices(WindowSizeCallback* callback) : window("OpenGl C++", 1280, 720, callback) {
    window.resize(1280, 720);
    window.setBackgroundColor(0.25f, 0.25f, 0.25f);
}

Keyboard& Devices::keyboard() {
    return input.keyboard;
}

Mouse& Devices::mouse() {
    return input.mouse;
}

void Devices::update() {
    window.update();
    timer.update();
    input.update(Window::getWidth() / 2.f, Window::getHeight() / 2.f);
    window.clear();
}

void Devices::showWindow() {
    window.show();
}
