#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Renderer2D.h"
#include "SceneManager.h"
#include "TextureManager.h"
#include "Input.h"
#include "GCManager.h"
#include "GameInstance.h"	

class Engine {
public:

	Engine(int screenW, int screenH);

	void Run();

	int GetScreenW() const { return m_screenW; }
	int GetScreenH() const { return m_screenH; }

	Renderer2D& GetRenderer2D() { return renderer; }
	Input& GetInput() { return input; }
	TextureManager& GetTextureManager() { return textureM; }
	SceneManager& GetSceneManager() { return sceneM; }
	GameInstance* GetGameInstance() { return gameInstanceGC; }
private:
	GLFWwindow* m_window = nullptr;
	Renderer2D renderer;
	Input input;
	SceneManager sceneM;
	TextureManager textureM;

	GCManager gcM;
	GameInstance* gameInstanceGC = nullptr;

	bool running = true;
	float lastTime = 0;

	int m_screenW = 0;
	int m_screenH = 0;

	void EngineTick(float dt);


};


extern Engine* gEngine;