//#include "MaterialLoader.h"
//#include <fstream>
//#include <sstream>
//#include <map>
//#include <iostream>
//#include <cmath>
//
//std::map<std::string, Material> MaterialLoader::load(const std::string& filePath) {
//
//    std::ifstream file(filePath, std::ios::in);
//    std::vector<std::string> lines;
//    std::string lineRead;
//
//    if (!file.is_open()) {
//        throw std::runtime_error("File could not be found: " + std::string(filePath));
//    }
//
//    std::stringstream fileContent;
//
//    while (std::getline(file, lineRead)) {
//        lines.push_back(lineRead);
//    }
//
//    std::map<std::string, Material> materials;
//
//    size_t pos;
//    std::string materialName;
//    Vec3 diffuseColor;
//    Vec3 specularColor;
//    float intensity = 0.f;
//
//    for (std::string& line : lines) {
//
//        if (line.empty()) {
//            continue;
//        }
//
//        if (line.find("newmtl") != std::string::npos) {
//            pos = line.find("newmtl") + 7;
//            materialName = std::string(line.substr(pos, line.size()));
//        }
//
//        if (line.find("Ks") != std::string::npos) {
//            pos = line.find("Ks") + 3;
//            std::string value = line.substr(pos, line.length());
//            specularColor = parseVector(value);
//
//            intensity = sqrtf(specularColor[0] * specularColor[0] + specularColor[1] * specularColor[1] + specularColor[2] * specularColor[2]);
//        }
//
//        if (line.find("Kd") != std::string::npos) {
//            pos = line.find("Kd") + 3;
//            std::string value = line.substr(pos, line.length());
//            diffuseColor = parseVector(value);
//        }
//
//        if (line.find("illum") != std::string::npos) {
//            materials.emplace(materialName, Material(diffuseColor, specularColor, 20.f, intensity));
//        }
//    }
//
//
//    return materials;
//}
//
//Vec3 MaterialLoader::parseVector(std::string& line) {
//    std::vector<std::string> components = split(line, ' ');
//    size_t offset = 0;
//
//    return Vec3(
//            std::stof(components[0], &offset),
//            std::stof(components[1], &offset),
//            std::stof(components[2], &offset)
//    );
//}
//
//template<typename Out>
//void MaterialLoader::split(const std::string& line, char delimiter, Out result) {
//    std::stringstream ss(line);
//    std::string component;
//
//    while (getline(ss, component, delimiter)) {
//        *(result++) = component;
//    }
//}
//
//std::vector<std::string> MaterialLoader::split(const std::string& line, char delimiter) {
//    std::vector<std::string> components;
//    split(line, delimiter, std::back_inserter(components));
//    return components;
//}