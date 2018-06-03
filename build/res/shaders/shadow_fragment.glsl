#version 460 core

out float outColor;

void main() {
    outColor = gl_FragCoord.z;
}
