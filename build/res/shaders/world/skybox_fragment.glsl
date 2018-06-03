#version 440 core

in vec3 vertexPosition;

uniform samplerCube cubeMap;

out vec4 outColor;

void main() {
    outColor = texture(cubeMap, vertexPosition);
}
