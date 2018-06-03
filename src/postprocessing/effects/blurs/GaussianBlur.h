#pragma once

#include "HorizontalBlur.h"
#include "VerticalBlur.h"
#include "../Effect.h"

class GaussianBlur : public Effect {

private:
    HorizontalBlur horizontalStep1;
    VerticalBlur verticalStep1;
    HorizontalBlur horizontalStep2;
    VerticalBlur verticalStep2;

public:
    GaussianBlur();
    ~GaussianBlur() = default;

    void prepare() override;
    GLuint apply(GLuint textureId) override;
    GLuint finishUp(GLuint textureId) override;
};
