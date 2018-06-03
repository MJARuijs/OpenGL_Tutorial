#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 2) in vec2 inTexture;

uniform vec2 translation;
uniform vec2 scale;

uniform float aspectRatio;

out vec2 vertexTexture;

void main() {
    vertexTexture = inTexture;

    vec2 position = (translation + scale * inPosition.xy);
    position.x /= aspectRatio;

    gl_Position = vec4(position, 0, 1);
}
