#pragma once

#include <GL/glew.h>

class Effect {

public:
    virtual void prepare() = 0;

    virtual GLuint apply(GLuint targetId) = 0;

    virtual GLuint finishUp(GLuint targetId) = 0;
};
