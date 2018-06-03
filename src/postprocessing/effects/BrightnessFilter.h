#pragma once

#include "../QuadMesh.h"
#include "../../graphics/FBO.h"

class BrightnessFilter {

private:
    FBO fbo;
    ShaderProgram shaderProgram;
    QuadMesh quadMesh;

public:
    BrightnessFilter();
    ~BrightnessFilter() = default;

    void prepare();
    GLuint apply(GLuint targetFBO);
    GLuint finishUp(GLuint targetFBO);

};
