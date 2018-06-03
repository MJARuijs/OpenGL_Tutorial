#version 460 core

in vec2 passTextureCoords;

uniform sampler2D sampler;

out vec4 outColor;

void main() {
    vec4 color = texture(sampler, passTextureCoords);
    float brightness = color.r * 0.2126 + color.g * 0.7152 + color.b * 0.0722;
    outColor = color * brightness * brightness;
}
