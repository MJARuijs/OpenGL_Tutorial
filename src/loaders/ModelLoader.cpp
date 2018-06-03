#include <sstream>
#include <string>
#include <fstream>
#include <iterator>
#include <regex>
#include <iostream>

#include "ModelLoader.h"

Mesh* ModelLoader::load(ShaderProgram& shaderProgram, std::vector<std::string> lines) {
    vector<vector<float>> positions, normalList, textureCoords;
    vector<vector<int>> points;

    parseAttributes(lines, positions, normalList, textureCoords, points);

    vector<GLfloat> vertices;
    vector<GLfloat> normals;
    vector<GLfloat> texCoords;

    parseVertices(points, positions, vertices, 0);
    parseVertices(points, textureCoords, texCoords, 1);
    parseVertices(points, normalList, normals, 2);

    vector<GLuint> indices = generateIndices(points.size());

    return new Mesh(shaderProgram, vertices, normals, texCoords, indices);
}

Mesh* ModelLoader::load(ShaderProgram& shaderProgram, const std::string &filePath) {

    ifstream file(filePath, ios::in);
    vector<string> lines;
    string line;

    if (!file.is_open()) {
        throw std::runtime_error("File could not be found: " + std::string(filePath));
    }

    stringstream fileContent;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    return load(shaderProgram, lines);
}

void ModelLoader::parseAttributes(vector<string>& lines,
                                  vector<vector<float>>& positions,
                                  vector<vector<float>>& normals,
                                  vector<vector<float>>& textureCoords,
                                  vector<vector<int>>& points) {

    for (string& line : lines) {
        if (line.empty()) {
            continue;
        }

        string prefix = line.substr(0, 2);

        if (prefix == "v ") {
            string values = line.substr(2, (line.size()));
            positions.push_back(parseVector(values));
        }
        else if (prefix == "vt") {
            string values = line.substr(3, (line.size()));
            textureCoords.push_back(parseVector(values));
        }
        else if (prefix == "vn") {
            string values = line.substr(3, (line.size()));
            normals.push_back(parseVector(values));
        }
        else if (prefix == "f ") {
            string values = line.substr(2, (line.size()));
            vector<vector<int>> parsedPoints = parsePoints(values);
            for (const vector<int> &arr : parsedPoints) {
                points.push_back(arr);
            }
        }
    }
}

size_t ModelLoader::parseVertices(
        vector<vector<int>>& points,
        vector<vector<float>>& positions,
        vector<float>& vertices,
        int type) {

    size_t size = 0;

    for (vector<int> point : points) {

        if (point.size() > type) {
            int index = point[type];
            if (index != -1) {
                vector<float> position = positions[index];
                for (float f : position) {
                    vertices.push_back(f);
                }
                size = position.size();
            }
        }
    }
    return size;
}

vector<float> ModelLoader::parseVector(string& line) {
    vector<string> components = split(line, ' ');
    vector<float> values;
    size_t offset = 0;

    for (int i = 0; i < components.size(); i++) {
        values.push_back(stof(components[i], &offset));
    }

    return values;
}

vector<vector<int>> ModelLoader::parsePoints(string line) {
    vector<vector<int>> points;
    vector<string> components = split(line, ' ');
    size_t offset = 0;

    for (auto &component : components) {
        string parsedComponent = regex_replace(component, regex("/"), " ");

        vector<string> splitted = split(parsedComponent, ' ');
        vector<int> values;

        for (auto &j : splitted) {
            int value = 0;
            if (!j.empty()) {
                value = stoi(j, &offset);
            }
            values.push_back(value - 1);
        }
        points.push_back(values);
    }
    return points;
}

vector<GLuint> ModelLoader::generateIndices(const size_t count) {
    vector<GLuint> indices;
    for (unsigned int i = 0; i < count; i++) {
        indices.push_back(i);
    }
    return indices;
}

template<typename Out>
void ModelLoader::split(const string& line, char delimiter, Out result) {
    stringstream ss(line);
    string component;

    while (getline(ss, component, delimiter)) {
        *(result++) = component;
    }
}

vector<string> ModelLoader::split(const string& line, char delimiter) {
    vector<string> components;
    split(line, delimiter, back_inserter(components));
    return components;
}
