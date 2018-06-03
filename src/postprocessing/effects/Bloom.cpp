#include "Bloom.h"
#include "../../components/peripherals/Window.h"

void Bloom::prepare() {
    brightnessFilter.prepare();
}

GLuint Bloom::apply(GLuint textureId) {
    GLuint id = brightnessFilter.apply(textureId);

    blur.prepare();
    id = blur.apply(id);
    id = blur.finishUp(id);

    filterApplier.prepare();
    filteredTexture = textureId;
    return id;
}

GLuint Bloom::finishUp(GLuint originalFrameId) {
    return filterApplier.apply(originalFrameId, filteredTexture);
}
