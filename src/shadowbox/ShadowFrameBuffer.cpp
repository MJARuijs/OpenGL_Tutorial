//#include <stdexcept>
//#include <iostream>
//#include "ShadowFrameBuffer.h"
//
//ShadowFrameBuffer::ShadowFrameBuffer(int width, int height) : width(width), height(height) {
//    glGenFramebuffers(1, &id);
//    glBindFramebuffer(GL_FRAMEBUFFER, id);
//
//    glDrawBuffer(GL_NONE);
//    glReadBuffer(GL_NONE);
//
//    createDepthTexture();
//
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//}
//
//ShadowFrameBuffer::~ShadowFrameBuffer() {
//    glDeleteFramebuffers(1, &id);
//    id = 0;
//
//    glDeleteTextures(1, &depthTextureId);
//    depthTextureId = 0;
//}
//
//void ShadowFrameBuffer::bind() {
//    glBindFramebuffer(GL_FRAMEBUFFER, id);
//    glViewport(0, 0, width, height);
//}
//
//void ShadowFrameBuffer::unbind(int width, int height) {
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//    glViewport(0, 0, width, height);
//}
//
//void ShadowFrameBuffer::createDepthTexture() {
//    glGenTextures(1, &depthTextureId);
//    glBindTexture(GL_TEXTURE_2D, depthTextureId);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
//    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTextureId, 0);
//}
