#pragma once

#include "../QuadMesh.h"
#include "../../graphics/FBO.h"

class FilterApplier {

private:
    FBO fbo;
    ShaderProgram shaderProgram;
    QuadMesh quadMesh;

public:
    FilterApplier();
    ~FilterApplier() = default;

    void prepare();
    GLuint apply(GLuint originalTexture, GLuint filteredTexture);
    GLuint finishUp(GLuint targetFBO);

};