#pragma once

#include "../../../graphics/FBO.h"
#include "../../../graphics/shaders/ShaderProgram.h"
#include "../../QuadMesh.h"

class HorizontalBlur {

private:
    FBO fbo;
    ShaderProgram shaderProgram;
    QuadMesh quadMesh;

public:
    HorizontalBlur(int roughness);
    ~HorizontalBlur() = default;

    void prepare();
    GLuint apply(GLuint textureId);
};
