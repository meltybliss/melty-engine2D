#include "glad/glad.h"
#include "GLFW/glfw3.h"


class Engine {
public:

	Engine();

	void Run();
private:
	GLFWwindow* m_window = nullptr;
	bool running = true;
	float lastTime = 0;

	void EngineTick(float dt);


};