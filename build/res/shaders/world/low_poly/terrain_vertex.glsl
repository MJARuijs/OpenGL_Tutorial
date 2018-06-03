#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec3 inColor;

struct AmbientLight {
	vec3 color;
};

struct DirectionalLight {
	vec3 color;
	vec3 direction;
};

uniform AmbientLight ambient;
uniform DirectionalLight directional;

uniform vec4 waterPlane;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 passPosition;
out vec3 passNormal;

flat out vec3 passColor;

vec3 computeAmbientColor() {
	return inColor * ambient.color;
}

vec3 computeDirectional() {
	vec3 total = vec3(0.0);

	vec3 position = ((model * vec4(inPosition, 1.0)).xyz);
	vec3 normal = normalize((model * vec4(inNormal, 0.0)).xyz);

	// Diffuse
	vec3 lightDirection = normalize(directional.direction);
	float factor = clamp(dot(normal, lightDirection), 0.0, 1.0);
	total += inColor * directional.color * factor;

	// Specular
	vec3 toLightVector = normalize(directional.direction);
    vec3 reflectionVector = 2 * (dot(toLightVector, normal)) * normal - toLightVector;
    vec3 toCameraVector = normalize((inverse(view) * vec4(0, 0, 0, 1)).xyz - position);
//	total += 0.5 * inColor * directional.color * clamp(pow(dot(reflectionVector, toCameraVector), 10.0), 0.0, 1.0);

	return total;
}

void main() {
    vec3 ambientColor = computeAmbientColor();
	vec3 directionalColor = computeDirectional();

    passPosition = inPosition;
    passNormal = inNormal;
    passColor = ambientColor + directionalColor;

    vec4 worldPosition = model * vec4(inPosition, 1.0);
    gl_ClipDistance[0] = dot(waterPlane, worldPosition);

    gl_Position = projection * view * worldPosition;
}
