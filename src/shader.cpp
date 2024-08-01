#include <shader/shader.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    // Leer los archivos de shaders
    std::string vertexCode = readFile(vertexPath);
    std::string fragmentCode = readFile(fragmentPath);
    
    // Compilar shaders
    compileShader(vertexCode, fragmentCode);
}

void Shader::use() const {
    glUseProgram(shaderID);
}

GLuint Shader::getID() const {
    return shaderID;
}

void Shader::compileShader(const std::string& vertexSource, const std::string& fragmentSource) {
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    
    // Compilar vertex shader
    const char* vertexCodeCStr = vertexSource.c_str();
    glShaderSource(vertex, 1, &vertexCodeCStr, nullptr);
    glCompileShader(vertex);
    
    // Verificar errores de compilación
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 1024, nullptr, infoLog);
        std::cerr << "Vertex Shader Compilation Failed:\n" << infoLog << std::endl;
    }
    
    // Compilar fragment shader
    const char* fragmentCodeCStr = fragmentSource.c_str();
    glShaderSource(fragment, 1, &fragmentCodeCStr, nullptr);
    glCompileShader(fragment);
    
    
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 1024, nullptr, infoLog);
        std::cerr << "Fragment Shader Compilation Failed:\n" << infoLog << std::endl;
    }
    
    // Crear y enlazar el programa
    shaderID = glCreateProgram();
    glAttachShader(shaderID, vertex);
    glAttachShader(shaderID, fragment);
    glLinkProgram(shaderID);
    
    // Verificar errores de enlace
    glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderID, 1024, nullptr, infoLog);
        std::cerr << "Shader Program Linking Failed:\n" << infoLog << std::endl;
    }
    
    // Limpiar
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

std::string Shader::readFile(const std::string& path) {
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
