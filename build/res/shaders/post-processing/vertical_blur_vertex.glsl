#version 460 core

layout(location = 0) in vec2 inTextureCoords;

uniform int textureHeight;

out vec2 passTextureCoords[11];

void main() {

    vec2 centerTextureCoords = inTextureCoords * 0.5 + 0.5;
    float pixelSize = 1.0  / textureHeight;

    for (int i = -5; i < 5; i++) {
       passTextureCoords[i + 5] = centerTextureCoords + vec2(0.0, i * pixelSize);
    }

    gl_Position = vec4(inTextureCoords, 0.0, 1.0);
}
