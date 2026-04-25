#include "engine/SceneManager.h"

void SceneManager::Tick(float dt) {
	if (!curScene) return;
	curScene->Tick(dt);
}

void SceneManager::Render() {
	if (!curScene) return;
	curScene->Render();
}


bool SceneManager::ChangeCurrentScene(std::unique_ptr<IScene> scene) {
	if (!scene) return false;

	if (curScene) {
		curScene->Exit();
	}
	
	curScene = std::move(scene);

	curScene->Enter();

	return true;
}