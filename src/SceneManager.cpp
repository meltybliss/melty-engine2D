#include "SceneManager.h"

void SceneManager::Tick(float dt) {
	curScene->Tick(dt);
}

void SceneManager::Render() {

	curScene->Render();
}


bool SceneManager::SetCurrentScene(std::unique_ptr<IScene> scene) {
	if (!scene) return false;
	
	curScene = std::move(scene);
	return true;
}