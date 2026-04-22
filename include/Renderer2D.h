#pragma once 
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

class Renderer2D {
public:

	Renderer2D();

	void BeginFrame();
	void EndFrame();

private:

	unsigned int colorVAO = 0;
	unsigned int colorVBO = 0;
	unsigned int colorShaderProgram = 0;

	unsigned int spriteVAO = 0;
	unsigned int spriteVBO = 0;
	unsigned int spriteShaderProgram = 0;

	static std::string ReadFile(const std::string& path);
	static GLuint CompileShader(GLenum type, const std::string& source, const std::string& debugName);
	static GLuint LinkProgram(GLuint vertShader, GLuint fragShader, const std::string& debugName);
	static GLuint CreateShaderProgram(const std::string& vertPath, const std::string& fragPath);
};