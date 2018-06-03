#include "Timer.h"

Timer::Timer() {
    double startTime = glfwGetTime();
    lastTime = startTime;
    currentTime = startTime;
}

void Timer::update() {
    lastTime = currentTime;
    currentTime = glfwGetTime();
}

float Timer::time() {
    return (float)currentTime;
}

float Timer::delta() {
    return float(currentTime - lastTime);
}