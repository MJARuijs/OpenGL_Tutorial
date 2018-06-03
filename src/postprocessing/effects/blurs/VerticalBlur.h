#pragma once

#include "../../../graphics/FBO.h"
#include "../../QuadMesh.h"

class VerticalBlur {

private:

    ShaderProgram shaderProgram;
    QuadMesh quadMesh;

public:
    VerticalBlur(int roughness);
    ~VerticalBlur() = default;
    FBO fbo;
    void prepare();
    GLuint apply(GLuint textureId);
};
