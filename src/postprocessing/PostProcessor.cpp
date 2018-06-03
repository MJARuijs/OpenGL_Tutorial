#include "PostProcessor.h"
#include "../userinterface/Image.h"
#include "../components/peripherals/Window.h"
#include "../loaders/TextureLoader.h"

PostProcessor::PostProcessor() : originalFrame(COLOR_DEPTH_BUFFER, Window::getWidth(), Window::getHeight()) {
//    effects.push_back(new GaussianBlur());
    effects.push_back(new ContrastBooster());
    effects.push_back(new Bloom());
}

void PostProcessor::prepare() {
    originalFrame.bind();
    originalFrame.clear();
}

void PostProcessor::applyEffects() {
    GLuint id = originalFrame.textureId;

    for (int i = 0; i < effects.size() - 1; i++) {
        Effect* next = effects[i];
        next->prepare();
        id = next->apply(id);
        id = next->finishUp(id);
    }

    Effect* finalEffect = effects.back();
    finalEffect->prepare();
    id = finalEffect->apply(id);
    unbindFBOs();
    finalEffect->finishUp(id);
}

void PostProcessor::unbindFBOs() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, Window::getWidth(), Window::getWidth());
}
