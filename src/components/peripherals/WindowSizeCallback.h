#pragma once

struct WindowSizeCallback {
    virtual void onSizeChanged(int width, int height) = 0;
};