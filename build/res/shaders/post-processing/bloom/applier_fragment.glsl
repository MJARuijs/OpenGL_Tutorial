#version 460 core

in vec2 passTextureCoords;

uniform sampler2D originalTexture;
uniform sampler2D filteredTexture;

out vec4 outColor;

void main() {

    vec4 originalColor = texture(originalTexture, passTextureCoords);
    vec4 filteredColor = texture(filteredTexture, passTextureCoords);

    outColor = originalColor + filteredColor;
}
