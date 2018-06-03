#include "HorizontalBlur.h"
#include "../../../components/peripherals/Window.h"

HorizontalBlur::HorizontalBlur(int roughness) :
        fbo(COLOR_BUFFER, Window::getWidth() / roughness, Window::getHeight() / roughness),
        shaderProgram("res/shaders/post-processing/horizontal_blur_vertex.glsl", "res/shaders/post-processing/blur_fragment.glsl"),
        quadMesh(shaderProgram)

{}

void HorizontalBlur::prepare() {
    fbo.bind();
    fbo.clear();
}

GLuint HorizontalBlur::apply(GLuint textureId) {
    shaderProgram.start();
    shaderProgram.set("sampler", 0);
    shaderProgram.set("textureWidth", Window::getWidth());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    quadMesh.render();

    shaderProgram.stop();

    return fbo.textureId;
}
