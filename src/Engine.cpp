#include "Engine.h"


Engine::Engine(int screenW, int screenH) : m_screenW(screenW), m_screenH(screenH) {
	if (!glfwInit()) {
		running = false;
	}

	m_window = glfwCreateWindow(m_screenW, m_screenH, "Engine", nullptr, nullptr);

	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		running = false;
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, m_screenW, m_screenH);


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