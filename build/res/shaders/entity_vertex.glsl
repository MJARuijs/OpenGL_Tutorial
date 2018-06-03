#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexture;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 scale;

uniform mat4 DepthBiasMVP;

out vec3 vertexPosition;
out vec3 vertexNormal;
out vec2 vertexTexture;
out vec4 shadowCoords;

void main() {
	vertexPosition = inPosition;
	vertexNormal = inNormal;
	vertexTexture = inTexture;

    shadowCoords = DepthBiasMVP * vec4(inPosition, 1.0f);

	gl_Position = projection * view * model * vec4(scale * inPosition, 1.0f);
}