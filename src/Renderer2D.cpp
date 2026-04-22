#include "Renderer2D.h"

std::string Renderer2D::ReadFile(const std::string& path) {//static
	std::ifstream file(path);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file: " + path);
	}

	std::stringstream ss;
	ss << file.rdbuf();

	return ss.str();

}

GLuint Renderer2D::CompileShader(GLenum type, const std::string& source, const std::string& debugName) {
	//static

	GLuint shader = glCreateShader(type);

	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	GLint success = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		char infoLog[1024];
		glGetShaderInfoLog(shader, 1024, nullptr, infoLog);

		std::cerr << "Shader compile failed: " << debugName << "\n";
		std::cerr << infoLog << "\n";

		glDeleteShader(shader);

		throw std::runtime_error("Shader compile failed: " + debugName);
	}

	return shader;
}


GLuint Renderer2D::LinkProgram(GLuint vertShader, GLuint fragShader, const std::string& debugName) {
	//static
	GLuint program = glCreateProgram();

	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	GLint success = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success) {
		char infoLog[1024];
		glGetProgramInfoLog(program, 1024, nullptr, infoLog);

		std::cerr << "Program link failed: " << debugName << "\n";
		std::cerr << infoLog << "\n";

		glDeleteProgram(program);
		throw std::runtime_error("Program link failed: " + debugName);
	}

	return program;


}


GLuint Renderer2D::CreateShaderProgram(const std::string& vertPath, const std::string& fragPath) {

	std::string vertSource = ReadFile(vertPath);
	std::string fragSource = ReadFile(fragPath);

	GLuint vertShader = CompileShader(GL_VERTEX_SHADER, vertSource, vertPath);
	GLuint fragShader = CompileShader(GL_FRAGMENT_SHADER, fragSource, fragPath);

	GLuint program = LinkProgram(vertShader, fragShader, vertPath + " + " + fragPath);

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	return program;

}


Renderer2D::Renderer2D() {

	//color shader
	CreateShaderProgram("resources/shaders/color2d.vert", "resources/shaders/color2d.frag");

	glGenVertexArrays(1, &colorVAO);
	glGenBuffers(1, &colorVBO);

	glBindVertexArray(colorVAO);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, nullptr, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}