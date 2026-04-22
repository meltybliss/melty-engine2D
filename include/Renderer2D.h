#pragma once 
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

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

};