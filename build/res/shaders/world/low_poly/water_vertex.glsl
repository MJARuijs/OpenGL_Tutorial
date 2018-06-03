#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inNeighbours;

struct DirectionalLight {
	vec3 color;
	vec3 direction;
};

const float PI = 3.14159265;
const float waveLength = 4.0;
const float waveAmplitude = 3.3;

uniform DirectionalLight sun;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 cameraPosition;
uniform float moveFactor;

out vec3 passNormal;
out vec3 toCameraVector;
out vec4 actualPosition;
out vec4 distortedPosition;
out vec4 diffuseColor;
out vec4 specularColor;

float generateOffset(float x, float z, float val1, float val2) {
    float radiansX = ((mod(x+z*x*val1, waveLength)/waveLength) + moveFactor * mod(x * 0.8 + z, 1.5)) * 2.0 * PI;
    float radiansZ = ((mod(val2 * (z*x +x*z), waveLength)/waveLength) + moveFactor * 2.0 * mod(x , 2.0) ) * 2.0 * PI;
    return waveAmplitude * 0.5 * (sin(radiansZ) + cos(radiansX));
}

vec3 applyDistortion(vec3 vertex) {
    float xDistortion = generateOffset(vertex.x, vertex.z, 0.2, 0.1);
    float yDistortion = generateOffset(vertex.x, vertex.z, 0.1, 0.3);
    float zDistortion = generateOffset(vertex.x, vertex.z, 0.15, 0.2);

    return vertex + vec3(xDistortion, yDistortion, zDistortion);
}

vec3 calculateNormals(vec3 a, vec3 b, vec3 c) {
    vec3 v1 = b - a;
    vec3 v2 = c - a;
    return normalize(cross(v1, v2));
}

vec4 calculateSpecular(vec3 toCameraVector, vec3 toLightVector, vec3 normal) {
    vec3 reflectedLightDirection = reflect(-toLightVector, normal);
    float specularFactor = dot(reflectedLightDirection, toCameraVector);
    specularFactor = clamp(specularFactor, 0.0, 1.0);
    specularFactor = pow(specularFactor, 100);
    return specularFactor * vec4(sun.color, 1);
}

vec4 calculateDiffuse(vec3 toLightVector, vec3 normal) {
    float brightness = max(dot(toLightVector, normal), 0.0);
    return vec4(sun.color, 1) * brightness;
}

void main() {
    vec4 worldPosition = model * vec4(inPosition, 1.0);
    actualPosition = projection * view * model * vec4(inPosition, 1.0);
    toCameraVector = cameraPosition - worldPosition.xyz;

    vec3 distortedVertex = applyDistortion(vec3(inPosition));
    vec3 neighbour1 = inPosition + vec3(inNeighbours.x, 0, inNeighbours.y);
    vec3 neighbour2 = inPosition + vec3(inNeighbours.z, 0, inNeighbours.w);

    neighbour1 = applyDistortion(neighbour1);
    neighbour2 = applyDistortion(neighbour2);

    passNormal = calculateNormals(distortedVertex, neighbour1, neighbour2);

    vec3 toLightVector = normalize(sun.direction);
    diffuseColor = calculateDiffuse(toLightVector, passNormal);
    specularColor = calculateSpecular(toCameraVector, toLightVector, passNormal);

    distortedPosition = projection * view * model * vec4(distortedVertex, 1);
    gl_Position = distortedPosition;
}