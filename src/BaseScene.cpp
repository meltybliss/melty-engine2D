#include "BaseScene.h"

void BaseScene::Render() {
	renderSystem.Render(entityManager);
}