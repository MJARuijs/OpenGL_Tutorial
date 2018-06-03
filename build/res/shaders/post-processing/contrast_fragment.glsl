#version 460 core

in vec2 passTextureCoords;

const float contrast = 0.3;

uniform sampler2D sampler;

out vec4 outColor;

void main() {
    outColor = texture(sampler, passTextureCoords);
    outColor.rgb = (outColor.rgb - 0.5) * (1.0 + contrast) + 0.5;
}
