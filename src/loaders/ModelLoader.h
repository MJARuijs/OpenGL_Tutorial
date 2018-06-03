#pragma once
#include <string>
#include <vector>
#include "../graphics/objects/Mesh.h"
#include "../graphics/shaders/ShaderProgram.h"

using namespace std;

class ModelLoader {

private:
    static void parseAttributes(
            vector<string>& lines,
            vector<vector<float>>& positions,
            vector<vector<float>>& normals,
            vector<vector<float>>& textureCoords,
            vector<vector<int>>& points);

    static size_t parseVertices(
            vector<vector<int>>& points,
            vector<vector<float>>& positions,
            vector<float>& vertices,
            int type);

    static vector<float> parseVector(string& line);
    static vector<GLuint> generateIndices(size_t count);
    static vector<vector<int>> parsePoints(string line);

    template<typename Out>
    static void split(const string& line, char delimiter, Out result);
    static vector<string> split(const string& line, char delimiter);

public:
    static Mesh* load(ShaderProgram& shaderProgram, std::vector<std::string> lines);
    static Mesh* load(ShaderProgram& shaderProgram, const std::string& filePath);
};



