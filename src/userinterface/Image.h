#pragma once

#include <vector>

#include "../graphics/shaders/ShaderProgram.h"
#include "../graphics/objects/Mesh.h"
#include "../graphics/objects/material/Texture.h"
#include "../math/vectors/Vec2.h"
#define ALIGN_TOP_LEFT  0
#define ALIGN_BOTTOM_LEFT 1
#define ALIGN_TOP_RIGHT  2
#define ALIGN_BOTTOM_RIGHT 3

class Image {

private :
    Mesh* mesh;
    Texture* texture;
    GLuint textureId;
    Vec2 position;

public:
    Image(Mesh* mesh);
    Image(Mesh* mesh, Texture* texture);
    Image(Mesh* mesh, GLuint& textureID);
    ~Image() = default;

    int alignmentType;

    bool depthTexture;
    bool textured;
    Vec2 translation;
    Vec2 scale;

    void alignFromTopLeft(int width, int height);
    void alignFromBottomLeft(int width, int height);
    void alignFromTopRight(int width, int height);
    void alignFromBottomRight(int width, int height);

    void update(int width, int height);
    void render(ShaderProgram& shaderProgram);
    void destroy();
};


