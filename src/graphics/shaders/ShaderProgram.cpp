#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(Shader vertexShader, Shader fragmentShader) {
    programId = glCreateProgram();

    vertexShader.attachTo(programId);
    fragmentShader.attachTo(programId);

    glLinkProgram(programId);
    glValidateProgram(programId);

    GLint result;

    glGetProgramiv(programId, GL_VALIDATE_STATUS, &result);

    GLint linked = 0;
    glGetProgramiv(programId, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE) {

        GLint size = 0;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &size);

        GLchar log[size];
        glGetProgramInfoLog(programId, size, &size, log);

        glDeleteProgram(programId);

        throw std::runtime_error("Could not link program: \n" + std::string(log));
    }
}

ShaderProgram::ShaderProgram(const std::string &vertexPath, const std::string &fragmentPath) :
        ShaderProgram(Shader(GL_VERTEX_SHADER, vertexPath), Shader(GL_FRAGMENT_SHADER, fragmentPath))
{}

ShaderProgram::~ShaderProgram() {
    stop();
    glDeleteProgram(programId);
}

void ShaderProgram::setAttribute(GLuint location, GLuint size, GLuint type, GLboolean normalized, GLuint stride, GLvoid* offset) {
    glVertexAttribPointer(location, size, type, normalized, stride, offset);
    glEnableVertexAttribArray(location);
}

GLint ShaderProgram::getUniformLocation(const char* name) {
    auto iterator = uniformLocations.find(name);
    if (iterator != uniformLocations.end()) {
        return iterator->second;
    }
    GLint location = glGetUniformLocation(programId, name);
    uniformLocations.emplace(name, location);
    return location;
}

void ShaderProgram::start() {
    glUseProgram(programId);
}

void ShaderProgram::set(const char *name, bool value) {
    set(name, value ? 1 : 0);
}

void ShaderProgram::set(const char *name, GLuint value) {
    GLint location = getUniformLocation(name);
    glUniform1i(location, value);
}

void ShaderProgram::set(const char *name, int value) {
    GLint location = getUniformLocation(name);
    glUniform1i(location, value);
}

void ShaderProgram::set(const char *name, float value) {
    GLint location = getUniformLocation(name);
    glUniform1f(location, value);
}

void ShaderProgram::set(const char *name, Vec2 vector) {
    GLint location = getUniformLocation(name);
    glUniform2f(location, vector[0], vector[1]);
}

void ShaderProgram::set(const char *name, Vec3 vector) {
    GLint location = getUniformLocation(name);
    glUniform3f(location, vector[0], vector[1], vector[2]);
}

void ShaderProgram::set(const char *name, Vec4 vector) {
    GLint location = getUniformLocation(name);
    glUniform4f(location, vector[0], vector[1], vector[2], vector[3]);
}

void ShaderProgram::set(const char *name, Mat4 matrix) {
    GLint location = getUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_TRUE, &matrix.matrix[0][0]);
}

void ShaderProgram::stop() {
    glUseProgram(0);
}
