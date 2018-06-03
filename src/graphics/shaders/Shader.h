#pragma once
#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>

class Shader {

private:
	GLuint shaderId;

public:
	Shader(GLenum type, const std::string& filePath);
	~Shader();

	void attachTo(GLuint id);
};

