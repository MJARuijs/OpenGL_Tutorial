#pragma once

#include "../../graphics/FBO.h"
#include "../QuadMesh.h"
#include "blurs/GaussianBlur.h"
#include "BrightnessFilter.h"
#include "FilterApplier.h"
#include "Effect.h"

class Bloom : public Effect {

private:
    BrightnessFilter brightnessFilter;
    FilterApplier filterApplier;
    GaussianBlur blur;
    GLuint filteredTexture;

public:
    Bloom() = default;
    ~Bloom() = default;

    void prepare() override;
    GLuint apply(GLuint textureId) override;
    GLuint finishUp(GLuint originalFrameId) override;
};
