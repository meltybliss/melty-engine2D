#pragma once 
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "RenderCommand.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <algorithm>

class Renderer2D {
public:

	Renderer2D() = default;
	void Init();

	void BeginFrame();
	void EndFrame();

	void SubmitTriangle(const Vec2& a, const Vec2& b, const Vec2& c, const Color3& color, int layer);
	void SubmitQuad(const Vec2& a, const Vec2& b, const Vec2& c, const Vec2& d, const Color3& color, int layer);
	void SubmitRect(float x, float y, float w, float h, const Color3& color, int layer);
	void SubmitSprite(Texture2D* texture, float x, float y, const Color3& color, int layer);

private:

	unsigned int colorVAO = 0;
	unsigned int colorVBO = 0;
	unsigned int colorShaderProgram = 0;

	unsigned int spriteVAO = 0;
	unsigned int spriteVBO = 0;
	unsigned int spriteShaderProgram = 0;

	unsigned int curProgram = 0;

	std::vector<RenderCommand> renderCommands;

	GLint screenSizeLoc = 0;
	GLint colorLoc = 0;

	GLint screenSizeLoc2 = 0;
	GLint colorLoc2 = 0;
	GLuint texLoc = 0;

	static std::string ReadFile(const std::string& path);
	static GLuint CompileShader(GLenum type, const std::string& source, const std::string& debugName);
	static GLuint LinkProgram(GLuint vertShader, GLuint fragShader, const std::string& debugName);
	static GLuint CreateShaderProgram(const std::string& vertPath, const std::string& fragPath);
};