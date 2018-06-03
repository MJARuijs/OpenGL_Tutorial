#pragma once

#include "../graphics/objects/material/Texture.h"
#include "../graphics/objects/Mesh.h"
#include "../graphics/FBO.h"
#include "QuadMesh.h"
#include "effects/ContrastBooster.h"
#include "effects/blurs/GaussianBlur.h"
#include "effects/Bloom.h"
#include <list>

class PostProcessor {

private:
    std::vector<Effect*> effects;

    FBO originalFrame;

public:
    PostProcessor();
    ~PostProcessor() = default;

    void prepare();
    void applyEffects();
    void unbindFBOs();
};
