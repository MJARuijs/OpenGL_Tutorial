#pragma once

#include "../graphics/objects/Mesh.h"
#include "TerrainMesh.h"
#include "../graphics/objects/material/Color.h"
#include "../math/PerlinNoise.h"
#include "ColorGenerator.h"

namespace TerrainGenerator {

    namespace {
        int smoothness = 7;
        std::vector<GLfloat> vertices;
        std::vector<GLfloat> normals;
        std::vector<GLfloat> colors;
        std::vector<GLuint> indices;
        std::vector<Vec3> points;
        std::vector<Vec3> normalArray;

        Vec3 calculateNormal(Vec3 a, Vec3 b, Vec3 c) {
            Vec3 v1 = b - a;
            Vec3 v2 = c - a;
            Vec3 cross = v1.cross(v2).getNormalized();
            return cross;
        }

        template<size_t size>
        void generateSquare(float x, float z, int index, float heightMap[size][size]) {
            auto xIndex = (int)(x);
            auto zIndex = (int)(z);
            Vec3 pointA(x, heightMap[xIndex][zIndex], z);
            Vec3 pointB(x, heightMap[xIndex][zIndex + 1], z + 1);
            Vec3 pointC(x + 1, heightMap[xIndex + 1][zIndex + 1], z + 1);
            Vec3 pointD(x + 1, heightMap[xIndex + 1][zIndex], z);

            points.emplace_back(pointC);
            points.emplace_back(pointA);
            points.emplace_back(pointB);

            points.emplace_back(pointA);
            points.emplace_back(pointC);
            points.emplace_back(pointD);

            normalArray.emplace_back(calculateNormal(pointA, pointB, pointC));
            normalArray.emplace_back(calculateNormal(pointA, pointB, pointC));
            normalArray.emplace_back(calculateNormal(pointA, pointB, pointC));

            normalArray.emplace_back(calculateNormal(pointD, pointA, pointC));
            normalArray.emplace_back(calculateNormal(pointD, pointA, pointC));
            normalArray.emplace_back(calculateNormal(pointD, pointA, pointC));

            indices.emplace_back(index);
            indices.emplace_back(index + 1);
            indices.emplace_back(index + 2);

            indices.emplace_back(index + 3);
            indices.emplace_back(index + 4);
            indices.emplace_back(index + 5);
        }
    }

    template<size_t size>
    TerrainMesh* generateTerrain(ShaderProgram& shaderProgram, std::vector<Color>& biomeColors) {
        vertices.clear();
        normals.clear();
        indices.clear();
        colors.clear();
        points.clear();

        PerlinNoise pn(10164313);

        float heightMap[size][size];

        for (int x = 0; x < size - 1; x++) {
            for (int z = 0; z < size - 1; z++) {
                heightMap[x][z] = ((float) (pn.noise((float)x / 6, 0, (float)z / 6)) * 2.0f - 1.0f) * 75.0f;
            }
        }

        int index = 0;
        for (int x = 0; x < size - 1; x++) {
            for (int z = 0; z < size - 1; z++) {
                generateSquare(x, z, index, heightMap);
                index += 6;
            }
        }

        ColorGenerator colorGenerator(biomeColors, 0.45f);
        ColorTable<size> generatedColors = colorGenerator.generate(heightMap, 75.0f);

        for (Vec3 point : points) {
            vertices.emplace_back(point[0] * smoothness);
            vertices.emplace_back(point[1]);
            vertices.emplace_back(point[2] * smoothness);

            ColorRow<size> colorRow = generatedColors[point[0]];
            Color color = colorRow[point[2]];

            colors.emplace_back(color.getR());
            colors.emplace_back(color.getG());
            colors.emplace_back(color.getB());
        }

        for (Vec3 normal : normalArray) {
            normals.emplace_back(normal[0]);
            normals.emplace_back(normal[1]);
            normals.emplace_back(normal[2]);
        }

        return new TerrainMesh(shaderProgram, vertices, normals, colors, indices);
    }
};
