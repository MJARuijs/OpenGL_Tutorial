#version 460 core

struct DirectionalLight {
	vec3 color;
	vec3 direction;
};

uniform DirectionalLight sun;
uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D dudvMap;
uniform sampler2D normalMap;
uniform sampler2D depthTexture;

uniform mat4 model;
uniform mat4 view;
uniform float moveFactor;

in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 toCameraVector;
in vec4 transformedPosition;

out vec4 outColor;

float linearizeDepth(float depth) {
    float zNear = 0.1;
    float zFar = 1000.0;

//    return (2.0 * zNear) / (zFar + zNear - depth * (zFar - zNear));
    return 2.0 * zNear * zFar / (zFar + zNear - (2.0 * depth - 1.0) * (zFar - zNear));
}

void main() {

    vec2 ndc = (transformedPosition.xy / transformedPosition.w) / 2.0 + 0.5;

    vec2 reflectionCoords = vec2(ndc.x, 1 - ndc.y);
    vec2 refractionCoords = vec2(ndc.x, ndc.y);

    float depth = texture(depthTexture, refractionCoords).x;
    float lakeBottomDistance = linearizeDepth(depth);

    depth = gl_FragCoord.z;
    float waterDistance = linearizeDepth(depth);
    float waterDepth = lakeBottomDistance - waterDistance;

    float opacity = clamp(waterDepth * 5.0, 0.0, 1.0);

    vec2 distortion = texture(dudvMap, vec2(vertexTexCoord.x + moveFactor, vertexTexCoord.y)).rg * 0.1;
    distortion = vertexTexCoord + vec2(distortion.x, distortion.y + moveFactor);
    vec2 totalDistortion = (texture(dudvMap, distortion).rg * 2.0 - 1.0) * 0.02;

    reflectionCoords += totalDistortion;
    refractionCoords += totalDistortion;

    vec4 reflectionColor = texture(reflectionTexture, reflectionCoords);
    vec4 refractionColor = texture(refractionTexture, refractionCoords);

    vec4 normalColor = texture(normalMap, distortion);
    vec3 normal = vec3(normalColor.r * 2.0 - 1.0, normalColor.b, normalColor.g * 2.0 - 1.0);
    normal = normalize(normal);

    vec3 toLightVector = normalize(sun.direction);
	vec3 reflectionVector = 2 * (dot(toLightVector, normal)) * normal - toLightVector;
    vec3 specularColor = 0.0 * opacity * sun.color * clamp(pow(dot(reflectionVector, toCameraVector), 100.f), 0.0, 1.0);

    float reflectivity = dot(normalize(toCameraVector), normal);

    outColor = vec4(specularColor, opacity) + mix(outColor, vec4(0, 0.2, 0.4, 1), 0.2) + mix(reflectionColor, refractionColor, reflectivity);
    outColor.a = opacity;
}
