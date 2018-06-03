#pragma once

#include "input/Input.h"
#include "Timer.h"

class Devices {

public:
    Devices(WindowSizeCallback*);
    ~Devices() = default;

    Window window;
    Timer timer;
    Input input;

    Keyboard& keyboard();
    Mouse& mouse();

    void update();
    void showWindow();
};

