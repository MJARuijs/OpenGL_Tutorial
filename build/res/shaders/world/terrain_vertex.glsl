#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 scale;

uniform vec4 waterPlane;
uniform mat4 DepthBiasMVP;

out vec3 vertexPosition;
out vec3 vertexNormal;
out vec4 shadowCoords;

void main() {
    vertexPosition = inPosition;
    vertexNormal =  inNormal;

    shadowCoords = DepthBiasMVP * vec4(inPosition, 1);

    vec4 worldPosition = model * vec4(scale * inPosition, 1.0f);
    gl_ClipDistance[0] = dot(waterPlane, worldPosition);

    gl_Position = projection * view * worldPosition;
}
