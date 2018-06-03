#pragma once

#include <vector>
#include <cmath>
#include "../graphics/objects/material/Color.h"
#include "../standard.h"

class ColorGenerator {

private:
    float spread;
    float halfSpread;
    float part;
    std::vector<Color> colors;

    Color calculateColor(float height, float amplitude) {
        float value = (height + amplitude) / (amplitude * 2);
        value = fmaxf(fminf((value - halfSpread) * (1.0f / spread), 1.0f), 0.f);
        auto index = (int) floorf(value / part);
        float blendFactor = (value - (index * part)) / part;
        return Color::interpolateColors(colors[index], colors[index + 1], blendFactor);
    }

public:
    ColorGenerator(const std::vector<Color> &colors, float spread) :
            colors(colors),
            spread(spread),
            halfSpread(spread / 2.0f),
            part (1.0f / (colors.size() - 1))
    {}

    ~ColorGenerator() = default;

    template<size_t size>
    ColorTable<size> generate(float heightMap[size][size], float amplitude) {

        ColorTable<size> table;

        for (int x = 0; x < size; x++) {
            for (int z = 0; z < size; z++) {
                table[x][z] = calculateColor(heightMap[x][z], amplitude);
            }
        }

        return table;
    }

};
