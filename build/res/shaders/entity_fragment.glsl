#version 460 core

struct Material {
    sampler2D sampler;
	vec3 diffuseColor;
	vec3 specularColor;
	bool textured;
	float shininess;
	float intensity;
};

struct AmbientLight {
	vec3 color;
};

struct DirectionalLight {
	vec3 color;
	vec3 direction;
};

struct PointLight {
	vec3 color;
	vec3 position;
};

struct Attenuation {
	float constant;
	float linear;
	float quadratic;
};

uniform Material material;
uniform AmbientLight ambient;
uniform DirectionalLight directional;
uniform PointLight pointLight[2];

uniform Attenuation attenuation;

uniform mat4 model;
uniform mat4 view;

uniform sampler2D shadowMap;

in vec3 vertexPosition;
in vec3 vertexNormal;
in vec2 vertexTexture;
in vec4 shadowCoords;

out vec4 outColor;

vec3 computeAmbientColor() {
    if (material.textured) {
        return texture2D(material.sampler, vertexTexture).xyz * ambient.color;
    }
	return material.diffuseColor * ambient.color;
}

vec3 computeDirectional() {
	vec3 total = vec3(0.0);

	vec3 position = ((model * vec4(vertexPosition, 1.0)).xyz);
	vec3 normal = normalize((model * vec4(vertexNormal, 0.0)).xyz);

	// Diffuse
	vec3 lightDirection = normalize(directional.direction);
	float factor = clamp(dot(normal, lightDirection), 0.0, 1.0);

	if (material.textured) {
		total += texture2D(material.sampler, vertexTexture).xyz * directional.color * factor;
	} else {
		total += material.diffuseColor * directional.color * factor;
	}

    // Specular
	vec3 toLightVector = normalize(directional.direction);
	vec3 reflectionVector = 2 * (dot(toLightVector, normal)) * normal - toLightVector;
	vec3 toCameraVector = normalize((inverse(view) * vec4(0, 0, 0, 1)).xyz - position);

	if (material.textured) {
		total += texture2D(material.sampler, vertexTexture).xyz * directional.color * clamp(pow(dot(reflectionVector, toCameraVector), material.shininess), 0.0, 1.0);
	} else {
		total += material.intensity * material.specularColor * directional.color * clamp(pow(dot(reflectionVector, toCameraVector), material.shininess), 0.0, 1.0);
	}

	return total;
}

vec3 computePointLights() {
	vec3 total = vec3(0.0);

	vec3 position = normalize((model * vec4(vertexPosition, 1.0)).xyz);
	vec3 normal = normalize((model * vec4(vertexNormal, 0.0)).xyz);

    for (int i = 0; i < 2; i++) {

        // Diffuse
        vec3 lightDirection = (pointLight[i].position - position);
        float factor = max(dot(normal, normalize(lightDirection)), 0.0);
    
        float distance = length(lightDirection);
        float attenuationFactor = attenuation.constant;
        attenuationFactor += attenuation.linear / distance;
        attenuationFactor += attenuation.quadratic / distance * distance;
    
        if (material.textured) {
            total += texture2D(material.sampler, vertexTexture).xyz * pointLight[i].color * factor * attenuationFactor;
        } else {
            total += material.diffuseColor * pointLight[i].color * factor * attenuationFactor;
        }
    
    	// Specular
    	vec3 toLightVector = normalize(pointLight[i].position - position);
    	vec3 reflectionVector = 2 * (dot(toLightVector, normal)) * normal - toLightVector;
    	vec3 toCameraVector = normalize((inverse(view) * vec4(0, 0, 0, 1)).xyz - position);
    
    	distance = length(pointLight[i].position - position);
    	attenuationFactor = attenuation.constant;
    	attenuationFactor += attenuation.linear / distance;
    	attenuationFactor += attenuation.quadratic / distance * distance;
    
    	if (material.textured) {
    		total += texture2D(material.sampler, vertexTexture).xyz * pointLight[i].color * clamp(pow(dot(reflectionVector, toCameraVector), material.shininess), 0.0, 1.0) * attenuationFactor;
    	} else {
    		total += material.intensity * material.specularColor * pointLight[i].color * clamp(pow(dot(reflectionVector, toCameraVector), material.shininess), 0.0, 1.0) * attenuationFactor;
    	}
    }

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
	vec3 pointLightColor = computePointLights();

    float shadow = computeShadowFactor();

	outColor = vec4(directionalColor + ambientColor, 1.0);
	outColor = clamp(outColor, 0.0, 1.0);
//	outColor = vec4(1);
}
