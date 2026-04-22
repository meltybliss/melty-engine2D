#include "Engine.h"


Engine::Engine() {
	if (!glfwInit()) {
		running = false;
	}

	m_window = glfwCreateWindow(1280, 720, "Engine", nullptr, nullptr);

	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		running = false;
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, 1280, 720);


	lastTime = (float)glfwGetTime();

}


void Engine::Run() {

	while (running && !glfwWindowShouldClose(m_window)) {
		float curTime = (float)glfwGetTime();
		float deltaTime = curTime - lastTime;
		lastTime = curTime;

		glfwPollEvents();

		this->EngineTick(deltaTime);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//render

		glfwSwapBuffers(m_window);

	}

	glfwDestroyWindow(m_window);
	glfwTerminate();

}



void Engine::EngineTick(float dt) {


}