#pragma once

#include <map>
#include "Shader.h"
#include "../../math/vectors/Vec3.h"
#include "../../math/matrices/Mat4.h"
#include "../../math/vectors/Vec2.h"

class ShaderProgram {

private:
    GLuint programId;
    std::map<const char*, GLint> uniformLocations;

public:
    ShaderProgram(Shader vertexShader, Shader fragmentShader);
    ShaderProgram(const std::string &vertexPath, const std::string &fragmentPath);
    ~ShaderProgram();

    void start();
    void setAttribute(GLuint location, GLuint size, GLuint type, GLboolean normalized, GLuint stride, GLvoid* offset);
    GLint getUniformLocation(const char* name);
    void set(const char *name, bool value);
    void set(const char *name, GLuint value);
    void set(const char *name, int value);
    void set(const char *name, float value);
    void set(const char *name, Vec2 vector);
    void set(const char *name, Vec3 vector);
    void set(const char *name, Vec4 vector);
    void set(const char *name, Mat4 matrix);
    void stop();
};

