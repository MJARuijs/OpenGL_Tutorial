#pragma once

#include <GL/glew.h>
#define COLOR_BUFFER 0
#define DEPTH_BUFFER 1
#define COLOR_DEPTH_BUFFER 2

class FBO {

private:
    GLuint id;
    int type;
    int width;
    int height;

public:
    FBO(int type, int width, int height);
    ~FBO();

    GLuint textureId;
    GLuint depthTextureId;
    GLuint depthBufferId;

    void createTexture();
    void createDepthTexture();
    void createDepthBuffer();

    void clear();
    void bind();
    void unbind(int width, int height);
};
