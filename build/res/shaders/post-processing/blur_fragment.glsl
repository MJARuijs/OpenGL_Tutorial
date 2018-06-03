#version 460 core

in vec2 passTextureCoords[11];

uniform sampler2D sampler;

out vec4 outColor;

void main() {
    outColor = vec4(0.0);

    outColor += texture(sampler, passTextureCoords[0]) * 0.0093;
    outColor += texture(sampler, passTextureCoords[1]) * 0.028002;
    outColor += texture(sampler, passTextureCoords[2]) * 0.065984;
    outColor += texture(sampler, passTextureCoords[3]) * 0.121703;
    outColor += texture(sampler, passTextureCoords[4]) * 0.175713;
    outColor += texture(sampler, passTextureCoords[5]) * 0.198596;
    outColor += texture(sampler, passTextureCoords[6]) * 0.175713;
    outColor += texture(sampler, passTextureCoords[7]) * 0.121703;
    outColor += texture(sampler, passTextureCoords[8]) * 0.065984;
    outColor += texture(sampler, passTextureCoords[9]) * 0.028002;
    outColor += texture(sampler, passTextureCoords[10]) * 0.0093;
}
