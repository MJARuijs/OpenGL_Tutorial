#version 460 core

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D depthTexture;

in vec3 passNormal;
in vec3 toCameraVector;
in vec4 actualPosition;
in vec4 distortedPosition;
in vec4 diffuseColor;
in vec4 specularColor;

out vec4 outColor;

float linearizeDepth(float depth) {
    float zNear = 0.1;
    float zFar = 1000.0;
    return 2.0 * zNear * zFar / (zFar + zNear - (2.0 * depth - 1.0) * (zFar - zNear));
}

vec2 calculateTextureCoords(vec4 clipSpace) {
    vec2 ndc = (clipSpace.xy / clipSpace.w) / 2.0 + 0.5;
    return clamp(ndc, 0.002, 0.998);
}

vec4 applyDepthColor(vec4 refractionColor, float waterDepth) {
    float factor = smoothstep(0, 1, waterDepth);
    float murkiness = 0.1 + factor * 0.75;
    return mix(refractionColor, vec4(0.404, 0.47, 0.851, 1.0), murkiness);
}

void main() {
    vec2 actualTexCoords = calculateTextureCoords(distortedPosition);
    vec2 distortedTexCoords = calculateTextureCoords(actualPosition);

    vec2 reflectionCoords = vec2(distortedTexCoords.x, 1 - distortedTexCoords.y);
    vec2 refractionCoords = distortedTexCoords;

    float depth = texture(depthTexture, actualTexCoords).x;
    float lakeBottomDistance = linearizeDepth(depth);

    depth = gl_FragCoord.z;
    float waterDistance = linearizeDepth(depth);
    float waterDepth = lakeBottomDistance - waterDistance;

    float opacity = clamp(waterDepth * 2.0, 0.0, 1.0);

    vec4 reflectionColor = texture(reflectionTexture, reflectionCoords);
    vec4 refractionColor = texture(refractionTexture, refractionCoords);

    refractionColor = applyDepthColor(refractionColor, waterDepth);

    float reflectivity = dot(normalize(toCameraVector), passNormal);

    outColor = mix(reflectionColor, refractionColor, reflectivity);
    outColor = outColor * diffuseColor + specularColor * 0.2;
//    outColor = specularColor;
    outColor.a = opacity;
}
