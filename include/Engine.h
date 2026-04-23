#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Renderer2D.h"
#include "SceneManager.h"
#include "Input.h"

class Engine {
public:

	Engine(int screenW, int screenH);

	void Run();

	int GetScreenW() const { return m_screenW; }
	int GetScreenH() const { return m_screenH; }

	Renderer2D& GetRenderer2D() { return renderer; }
	Input& GetInput() { return input; }
private:
	GLFWwindow* m_window = nullptr;
	Renderer2D renderer;
	Input input;
	SceneManager sceneM;

	bool running = true;
	float lastTime = 0;

	int m_screenW = 0;
	int m_screenH = 0;

	void EngineTick(float dt);


};


extern Engine* gEngine;