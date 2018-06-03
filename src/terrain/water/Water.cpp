#include <cmath>
#include "Water.h"

Water::Water(ShaderProgram &shaderProgram, WaterMesh* waterTile, Vec3 position) :
        waterTile(waterTile),
        scale(3.0f),
        height(position[1]),
        reflectionFbo(COLOR_BUFFER, 1024, 1024),
        refractionFbo(COLOR_DEPTH_BUFFER, 1024, 1024)
{
    transformation.setIdentity();
    transformation.translate(position, transformation);
    transformation.rotateX((float)M_PI_2);
}

float Water::getHeight() {
    return height;
}

void Water::render(ShaderProgram &shaderProgram, float delta) {
    shaderProgram.start();
    moveFactor += WAVE_SPEED * delta;
    shaderProgram.set("model", transformation);
    shaderProgram.set("moveFactor", moveFactor);
    waterTile->render();
    shaderProgram.stop();
}



