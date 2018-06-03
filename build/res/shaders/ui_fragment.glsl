#version 460 core

uniform sampler2D sampler;
uniform bool depthTexture;

in vec2 vertexTexture;

out vec4 outColor;

float linearize(in vec2 uv) {
    float zNear = 0.9;
    float zFar = 50.0;
    float depth = texture(sampler, uv).x;
    return (2.0 * zNear) / (zFar + zNear - depth * (zFar - zNear));
}

void main() {
    if (depthTexture) {
        float color = linearize(vertexTexture);
        outColor = vec4(color, color, color, 1.0);
    } else {
        outColor = texture(sampler, vertexTexture);
    }
}
