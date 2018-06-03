#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 scale;
uniform vec3 cameraPosition;

out vec3 vertexPosition;
out vec2 vertexTexCoord;
out vec3 toCameraVector;
out vec4 transformedPosition;

void main() {
    vertexPosition = inPosition;
    vertexTexCoord = inTexCoord;

    vec4 worldPosition = model * vec4(scale.x * inPosition.x, 0, scale.z * inPosition.y, 1.0);
    toCameraVector = cameraPosition - worldPosition.xyz;

    transformedPosition = projection * view * worldPosition;
    gl_Position = transformedPosition;
}
