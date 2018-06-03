#include "VerticalBlur.h"
#include "../../../components/peripherals/Window.h"

VerticalBlur::VerticalBlur(int roughness) :
        fbo(COLOR_DEPTH_BUFFER, Window::getWidth() / roughness, Window::getHeight() / roughness),
        shaderProgram("res/shaders/post-processing/vertical_blur_vertex.glsl", "res/shaders/post-processing/blur_fragment.glsl"),
        quadMesh(shaderProgram)

{}

void VerticalBlur::prepare() {
    fbo.bind();
    fbo.clear();
}

GLuint VerticalBlur::apply(GLuint textureId) {
    shaderProgram.start();
    shaderProgram.set("sampler", 0);
    shaderProgram.set("textureHeight", Window::getHeight());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    quadMesh.render();

    shaderProgram.stop();

    return fbo.textureId;
}
