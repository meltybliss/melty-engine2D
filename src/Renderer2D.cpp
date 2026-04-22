#include "Renderer2D.h"
#include "Engine.h"

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
	colorShaderProgram = CreateShaderProgram("resources/shaders/color2d.vert", "resources/shaders/color2d.frag");

	glGenVertexArrays(1, &colorVAO);
	glGenBuffers(1, &colorVBO);

	glBindVertexArray(colorVAO);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, nullptr, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	this->screenSizeLoc = glGetUniformLocation(colorShaderProgram, "uScreenSize");
	this->colorLoc = glGetUniformLocation(colorShaderProgram, "uColor");
}


void Renderer2D::SubmitTriangle(const Vec2& a, const Vec2& b, const Vec2& c, const Color3& color, int layer) {
	std::array<float, 6> vertices{
		a.x, a.y, 
		b.x, b.y,
		c.x, c.y
	};

	RenderCommand cmd{};
	cmd.type = CommandType::Triangle;
	cmd.useColor = true;
	cmd.layer = layer;
	cmd.triangle.color = color;
	cmd.triangle.vertices = vertices;


	renderCommands.push_back(cmd);
}


void Renderer2D::SubmitQuad(const Vec2& a, const Vec2& b, const Vec2& c, const Vec2& d, 
	const Color3& color, int layer) {

	std::array<float, 8> vertices{
		a.x, a.y,
		b.x, b.y,
		c.x, c.y,
		d.x, d.y
	};

	RenderCommand cmd{};
	cmd.type = CommandType::Quad;
	cmd.useColor = true;
	cmd.layer = layer;
	cmd.quad.color = color;
	cmd.quad.vertices = vertices;

	renderCommands.push_back(cmd);

}


void Renderer2D::SubmitRect(float x, float y, float w, float h, const Color3& color, int layer) {

	RenderCommand cmd{};
	cmd.type = CommandType::Rect;
	cmd.useColor = true;
	cmd.layer = layer;
	cmd.rect.x = x;
	cmd.rect.y = y;
	cmd.rect.w = w;
	cmd.rect.h = h;
	cmd.rect.color = color;

	renderCommands.push_back(cmd);
}


void Renderer2D::BeginFrame() {

	glViewport(0, 0, gEngine->GetScreenW(), gEngine->GetScreenH());
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}


void Renderer2D::EndFrame() {
	//sort by layer order
	std::sort(renderCommands.begin(), renderCommands.end(), [](const RenderCommand& a, const RenderCommand& b){
		return a.layer < b.layer;
	});

	//flush 
	for (auto& cmd : renderCommands) {

		if (cmd.useColor) {
			if (curProgram != colorShaderProgram) {

				curProgram = colorShaderProgram;
				glUseProgram(colorShaderProgram);

				glBindVertexArray(colorVAO);
				glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
			}

		}

		switch (cmd.type) {


			case CommandType::Triangle: {

			
				glUniform2f(screenSizeLoc, static_cast<float>(gEngine->GetScreenW()), static_cast<float>(gEngine->GetScreenH()));
				glUniform3f(colorLoc, cmd.triangle.color.r, cmd.triangle.color.g, cmd.triangle.color.b);


				glBufferData(GL_ARRAY_BUFFER, sizeof(cmd.triangle.vertices), cmd.triangle.vertices.data(), GL_DYNAMIC_DRAW);

				glDrawArrays(GL_TRIANGLES, 0, 3);
				break;
			}


			case CommandType::Quad: {
			
				glUniform2f(screenSizeLoc, static_cast<float>(gEngine->GetScreenW()), static_cast<float>(gEngine->GetScreenH()));
				glUniform3f(colorLoc, cmd.quad.color.r, cmd.quad.color.g, cmd.quad.color.b);

				
				auto& v = cmd.quad.vertices;


				//expected
				//4-----3
				//|		|
				//|     |
				//1-----2
				float final_vertices[]{
					//triangle 1
					v[0], v[1],
					v[2], v[3],
					v[4], v[5],

					//triangle2
					v[0], v[1],
					v[4], v[5],
					v[6], v[7]
				};


				glBufferData(GL_ARRAY_BUFFER, sizeof(final_vertices), final_vertices, GL_DYNAMIC_DRAW);

				glDrawArrays(GL_TRIANGLES, 0, 6);
				break;

			}


			case CommandType::Rect: {
				
				glUniform2f(screenSizeLoc, static_cast<float>(gEngine->GetScreenW()), static_cast<float>(gEngine->GetScreenH()));
				glUniform3f(colorLoc, cmd.rect.color.r, cmd.rect.color.g, cmd.rect.color.b);


				auto& r = cmd.rect;

				//expected
				//4-----3
				//|		|
				//|     |
				//1-----2
				float final_vertices[]{
					//triangle1
					r.x, r.y,
					r.x + r.w, r.y,
					r.x + r.w, r.y + r.h,

					//triangle2
					r.x, r.y,
					r.x + r.w, r.y + r.h,
					r.x, r.y + r.h
				};


				glBufferData(GL_ARRAY_BUFFER, sizeof(final_vertices), final_vertices, GL_DYNAMIC_DRAW);

				glDrawArrays(GL_TRIANGLES, 0, 6);
				break;

			}
		}

	}


	renderCommands.clear();
}