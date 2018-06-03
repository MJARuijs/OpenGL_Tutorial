
#include "FBO.h"
#define COLOR_BUFFER 0
#define DEPTH_BUFFER 1
#define COLOR_DEPTH_BUFFER 2

FBO::FBO(int type, int width, int height) : type(type), width(width), height(height) {
    glGenFramebuffers(1, &id);
    glBindFramebuffer(GL_FRAMEBUFFER, id);

    if (type == COLOR_BUFFER) {
        glDrawBuffer(GL_COLOR_ATTACHMENT0);
        createTexture();
    } else if (type == DEPTH_BUFFER) {
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        createDepthTexture();
    } else if (type == COLOR_DEPTH_BUFFER) {
        glDrawBuffer(GL_COLOR_ATTACHMENT0);
        createTexture();
        createDepthTexture();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FBO::~FBO() {
    glDeleteFramebuffers(1, &id);
    glDeleteRenderbuffers(1, &depthBufferId);
    glDeleteTextures(1, &textureId);
    glDeleteTextures(1, &depthTextureId);
    id = 0;
    depthBufferId = 0;
    textureId = 0;
    depthTextureId = 0;
}

void FBO::clear() {
    if (type == COLOR_BUFFER || type == COLOR_DEPTH_BUFFER) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    } else if (type == DEPTH_BUFFER) {
        glClear(GL_DEPTH_BUFFER_BIT);
    }
}

void FBO::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    glViewport(0, 0, width, height);
}

void FBO::unbind(int width, int height) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, width, height);
}

void FBO::createTexture() {
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glGenerateMipmap(GL_TEXTURE_2D);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureId, 0);
}

void FBO::createDepthTexture() {
    glGenTextures(1, &depthTextureId);
    glBindTexture(GL_TEXTURE_2D, depthTextureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTextureId, 0);
}

void FBO::createDepthBuffer() {
    glGenRenderbuffers(1, &depthBufferId);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBufferId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferId);
}
