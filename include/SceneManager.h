#pragma once
#include "IScene.h"
#include <memory>

class SceneManager {
public:

	void Tick(float dt);
	void Render();

	bool SetCurrentScene(std::unique_ptr<IScene> scene);
private:

	std::unique_ptr<IScene> curScene;

};