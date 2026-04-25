#pragma once
#include "IScene.h"
#include <memory>

class SceneManager {
public:

	void Tick(float dt);
	void Render();

	bool ChangeCurrentScene(std::unique_ptr<IScene> scene);
	IScene* GetCurrentScene() const { return curScene.get(); }
private:

	std::unique_ptr<IScene> curScene = nullptr;

};