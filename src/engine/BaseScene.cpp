#include "engine/BaseScene.h"
#include "engine/TextureAPI.h"



void BaseScene::Render() {
	renderSystem.Render(entityManager);
}
