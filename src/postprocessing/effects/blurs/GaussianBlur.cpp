#include "GaussianBlur.h"
#include "../../../components/peripherals/Window.h"

GaussianBlur::GaussianBlur() :
        horizontalStep1(2),
        verticalStep1(2),
        horizontalStep2(4),
        verticalStep2(4)
{}

void GaussianBlur::prepare() {
    horizontalStep1.prepare();
}

GLuint GaussianBlur::apply(GLuint textureId) {
    GLuint id = horizontalStep1.apply(textureId);

    verticalStep1.prepare();
    id = verticalStep1.apply(id);

    horizontalStep2.prepare();
    return horizontalStep2.apply(id);
}

GLuint GaussianBlur::finishUp(GLuint textureId) {
    verticalStep2.prepare();
    return verticalStep2.apply(textureId);
}
