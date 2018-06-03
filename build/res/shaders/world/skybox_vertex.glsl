#version 440 core

layout(location = 0) in vec3 inPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float distance;
uniform vec4 waterPlane;

out vec3 vertexPosition;

void main() {

    vertexPosition = inPosition;

    vec4 worldPosition = vec4(mat3(model) * inPosition * distance, 1.0);

    gl_ClipDistance[0] = dot(waterPlane, worldPosition);
    gl_Position = projection * vec4(mat3(view) * mat3(model) * inPosition * distance, 1);
}
