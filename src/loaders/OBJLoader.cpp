//#include "OBJLoader.h"
//#include "MaterialLoader.h"
//#include <map>
//#include <iostream>
//
//std::vector<Entity> OBJLoader::load(ShaderProgram& shaderProgram, const std::string &filePath, const std::string& materialFilePath) {
//    ifstream file(filePath, ios::in);
//    std::vector<std::string> lines;
//    std::string lineaRead;
//
//    if (!file.is_open()) {
//        throw std::runtime_error("File could not be found: " + std::string(filePath));
//    }
//
//    stringstream fileContent;
//
//    while (getline(file, lineaRead)) {
//        lines.push_back(lineaRead);
//    }
//
//    std::map<std::string, Material> materials = MaterialLoader::load(materialFilePath);
//    std::vector<Entity> entities;
//
//    std::string materialName = " ";
//    std::vector<std::string> meshData;
//
//    for (std::string& line : lines) {
//        if (line.empty()) {
//            continue;
//        }
//
//        if (line.find("usemtl") != std::string::npos) {
//            size_t pos = line.find("usemtl") + 7;
//            materialName = line.substr(pos, line.size());
//        } else if (line.find("o ") != std::string::npos) {
//            entities.emplace_back(shaderProgram, ModelLoader::load(shaderProgram, meshData), materials.find(materialName)->second);
//        } else {
//            meshData.push_back(line);
//        }
//
//    }
//
//    entities.emplace_back(shaderProgram, ModelLoader::load(shaderProgram, meshData), materials.find(materialName)->second);
//    return entities;
//
//}
//
//
