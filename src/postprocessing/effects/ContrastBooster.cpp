#include "ContrastBooster.h"
#include "../../components/peripherals/Window.h"

ContrastBooster::ContrastBooster() :
        fbo(COLOR_DEPTH_BUFFER, Window::getWidth(), Window::getHeight()),
        shaderProgram("res/shaders/post-processing/contrast_vertex.glsl", "res/shaders/post-processing/contrast_fragment.glsl"),
        quadMesh(shaderProgram)

{}

void ContrastBooster::prepare() {
    fbo.bind();
    fbo.clear();
}

GLuint ContrastBooster::apply(GLuint id) {
    shaderProgram.start();
    shaderProgram.set("sampler", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);

    return id;
}

GLuint ContrastBooster::finishUp(GLuint targetId) {
    quadMesh.render();
    shaderProgram.stop();
    return fbo.textureId;
}
