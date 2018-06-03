#version 460 core

struct AmbientLight {
	vec3 color;
};

struct DirectionalLight {
	vec3 color;
	vec3 direction;
};

struct Material {
    vec3 diffuseColor;
    vec3 specularColor;
    float shininess;
    float intensity;
};

uniform sampler2D shadowMap;
uniform AmbientLight ambient;
uniform DirectionalLight directional;
uniform Material material;

uniform mat4 model;
uniform mat4 view;

in vec3 vertexPosition;
in vec3 vertexNormal;
in vec4 shadowCoords;

out vec4 outColor;

vec3 computeAmbientColor() {
	return material.diffuseColor * ambient.color;
}

vec3 computeDirectional() {
	vec3 total = vec3(0.0);

	vec3 position = ((model * vec4(vertexPosition, 1.0)).xyz);
	vec3 normal = normalize((model * vec4(vertexNormal, 0.0)).xyz);

	// Diffuse
	vec3 lightDirection = normalize(directional.direction);
	float factor = clamp(dot(normal, lightDirection), 0.0, 1.0);
	total += material.diffuseColor * directional.color * factor;

	return total;
}

float computeShadowFactor() {
    vec3 coords = shadowCoords.xyz / shadowCoords.w;

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);

    for (int x = -1; x < 1; x++) {
        for (int y = -1; y < 1; y++) {
            float depth = texture(shadowMap, coords.xy + vec2(x, y) * texelSize).r;
            shadow += coords.z - 0.005 > depth ? 1.0 : 0.0;
        }
    }

    shadow /= 9.0;
    return 1.0 - shadow;
}

void main() {

    vec3 ambientColor = computeAmbientColor();
	vec3 directionalColor = computeDirectional();
    float shadow = computeShadowFactor();

    outColor = vec4(directionalColor + ambientColor, 1.0);
    outColor = clamp(outColor, 0.0, 1.0);
}
