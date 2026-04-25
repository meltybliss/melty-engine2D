#include "engine/Engine.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

Engine* gEngine = nullptr;

Engine::Engine(int screenW, int screenH) : m_screenW(screenW), m_screenH(screenH) {

	gEngine = this;

	if (!glfwInit()) {
		running = false;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_screenW, m_screenH, "Engine", nullptr, nullptr);
	if (!m_window) {
		running = false;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_window);

	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		running = false;
		return;
	}

	renderer.Init();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 330");


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

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		renderer.BeginFrame();

		sceneM.Render();

		renderer.EndFrame();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(m_window);

	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_window);
	glfwTerminate();


}



void Engine::EngineTick(float dt) {

	input.Tick(m_window);
	sceneM.Tick(dt);
}