#pragma once

#include "../../../math/vectors/Vec3.h"

class Color {

private:
    float r;
    float g;
    float b;

public:
    Color(float value, bool convert);
    Color(float r, float g, float b, bool convert);
    Color();
    ~Color() = default;

    float getR();
    float getG();
    float getB();

    Vec3 toVector();


    static Color interpolateColors(Color color1, Color color2, float mixFactor);
};
