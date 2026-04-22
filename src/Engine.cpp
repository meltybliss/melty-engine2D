#include "Engine.h"


Engine* gEngine;

Engine::Engine(int screenW, int screenH) : m_screenW(screenW), m_screenH(screenH) {

	gEngine = this;

	if (!glfwInit()) {
		running = false;
	}

	m_window = glfwCreateWindow(m_screenW, m_screenH, "Engine", nullptr, nullptr);

	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		running = false;
	}

	glEnable(GL_DEPTH_TEST);


	lastTime = (float)glfwGetTime();

}


void Engine::Run() {

	while (running && !glfwWindowShouldClose(m_window)) {
		float curTime = (float)glfwGetTime();
		float deltaTime = curTime - lastTime;
		lastTime = curTime;

		glfwPollEvents();

		this->EngineTick(deltaTime);

		

		//render

		glfwSwapBuffers(m_window);

	}

	glfwDestroyWindow(m_window);
	glfwTerminate();

}



void Engine::EngineTick(float dt) {


}