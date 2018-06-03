#pragma once

#include "../../graphics/FBO.h"
#include "../../graphics/shaders/ShaderProgram.h"
#include "../QuadMesh.h"
#include "Effect.h"

class ContrastBooster : public Effect {

private:
    FBO fbo;
    ShaderProgram shaderProgram;
    QuadMesh quadMesh;

public:
    ContrastBooster();

    void prepare() override ;
    GLuint apply(GLuint id) override;
    GLuint finishUp(GLuint targetId) override;
};
