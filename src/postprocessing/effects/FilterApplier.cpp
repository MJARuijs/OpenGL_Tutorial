#include "FilterApplier.h"
#include "../../components/peripherals/Window.h"

FilterApplier::FilterApplier() :
        fbo(COLOR_BUFFER, Window::getWidth(), Window::getHeight()),
        shaderProgram("res/shaders/post-processing/bloom/vertex.glsl", "res/shaders/post-processing/bloom/applier_fragment.glsl"),
        quadMesh(shaderProgram)
{}

void FilterApplier::prepare() {
    fbo.bind();
    fbo.clear();
}

GLuint FilterApplier::apply(GLuint originalTexture, GLuint filteredTexture) {
    shaderProgram.start();
    shaderProgram.set("originalTexture", 0);
    shaderProgram.set("filteredTexture", 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, originalTexture);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, filteredTexture);

    quadMesh.render();

    shaderProgram.stop();
    return fbo.textureId;
}

GLuint FilterApplier::finishUp(GLuint targetFBO) {
    return targetFBO;
}
