#include "glad/glad.h"
#include "GLFW/glfw3.h"


class Engine {
public:

	Engine(int screenW, int screenH);

	void Run();
private:
	GLFWwindow* m_window = nullptr;
	bool running = true;
	float lastTime = 0;

	int m_screenW = 0;
	int m_screenH = 0;

	void EngineTick(float dt);


};