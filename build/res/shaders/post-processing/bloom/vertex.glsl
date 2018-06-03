#version 460 core

layout(location = 0) in vec2 inTextureCoords;

out vec2 passTextureCoords;

void main() {
    passTextureCoords = inTextureCoords * 0.5 + 0.5;
    gl_Position = vec4(inTextureCoords, 0, 1);
}
