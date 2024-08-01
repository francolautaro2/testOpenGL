#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> 
#include <string>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    void use() const;
    GLuint getID() const;

private:
    GLuint shaderID;
    void compileShader(const std::string& vertexSource, const std::string& fragmentSource);
    std::string readFile(const std::string& path);
};

#endif // SHADER_H
