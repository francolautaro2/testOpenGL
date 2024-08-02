#include "OBJLoader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

bool loadOBJ(const std::string& path, Mesh& mesh) {
    std::vector<glm::vec3> temp_positions;
    std::vector<glm::vec3> temp_normals;
    std::vector<glm::vec2> temp_texCoords;
    std::vector<unsigned int> temp_indices;

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << path << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            glm::vec3 position;
            iss >> position.x >> position.y >> position.z;
            temp_positions.push_back(position);
        } else if (prefix == "vt") {
            glm::vec2 texCoord;
            iss >> texCoord.x >> texCoord.y;
            temp_texCoords.push_back(texCoord);
        } else if (prefix == "vn") {
            glm::vec3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            temp_normals.push_back(normal);
        } else if (prefix == "f") {
            unsigned int vertexIndex[3], texCoordIndex[3], normalIndex[3];
            char slash; // to discard the slashes in the format "v/t/n"
            for (int i = 0; i < 3; ++i) {
                iss >> vertexIndex[i] >> slash >> texCoordIndex[i] >> slash >> normalIndex[i];
                vertexIndex[i]--; // obj indices are 1-based
                texCoordIndex[i]--;
                normalIndex[i]--;
            }
            for (int i = 0; i < 3; ++i) {
                Vertex vertex;
                vertex.position = temp_positions[vertexIndex[i]];
                vertex.texCoords = temp_texCoords[texCoordIndex[i]];
                vertex.normal = temp_normals[normalIndex[i]];
                mesh.vertices.push_back(vertex);
                mesh.indices.push_back(mesh.vertices.size() - 1);
            }
        }
    }

    file.close();
    return true;
}
