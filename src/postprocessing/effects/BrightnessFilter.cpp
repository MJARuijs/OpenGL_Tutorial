#include "BrightnessFilter.h"
#include "../../components/peripherals/Window.h"

BrightnessFilter::BrightnessFilter() :
        fbo(COLOR_BUFFER, Window::getWidth(), Window::getHeight()),
        shaderProgram("res/shaders/post-processing/bloom/vertex.glsl", "res/shaders/post-processing/bloom/brightness_filter_fragment.glsl"),
        quadMesh(shaderProgram)
{}

void BrightnessFilter::prepare() {
    fbo.bind();
    fbo.clear();
}

GLuint BrightnessFilter::apply(GLuint targetFBO) {
    shaderProgram.start();
    shaderProgram.set("sampler", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, targetFBO);

    quadMesh.render();

    shaderProgram.stop();
    return fbo.textureId;
}

GLuint BrightnessFilter::finishUp(GLuint targetFBO) {
    return 0;
}
