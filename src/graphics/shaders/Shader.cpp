#include "Shader.h"

Shader::Shader(GLenum type, const std::string &filePath) {

    if (type != GL_VERTEX_SHADER && type != GL_FRAGMENT_SHADER) {
        std::runtime_error("Invalid Shader type!");
    }

    shaderId = glCreateShader(type);

    std::string shaderCode;
    std::ifstream shaderStream(filePath, std::ios::in);

    if (shaderStream.is_open()) {
        std::stringstream shaderString;
        shaderString << shaderStream.rdbuf();
        shaderCode = shaderString.str();
        shaderStream.close();
    }

    const GLchar* sourcePointer = shaderCode.c_str();

    glShaderSource(shaderId, 1, &sourcePointer, nullptr);
    glCompileShader(shaderId);

    GLint compiled;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compiled);

    if (!compiled) {
        GLint length;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
        auto * log = (GLchar*)malloc(static_cast<size_t>(length));
        glGetShaderInfoLog(shaderId, length, nullptr, log);
        printf("%s\n", log);
    }

}

Shader::~Shader() {
    glDeleteShader(shaderId);
}

void Shader::attachTo(GLuint id) {
    glAttachShader(id, shaderId);
}
