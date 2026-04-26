#pragma once
#include <stdint.h>
#include "EntityManager.h"
#include "SceneLogic.h"

struct EntitySnapshot {
	int id = -1;
	uint8_t alive = 1;
	std::string name;
	std::string tag;

	bool hasRenderer = false;
	RendererComponent rendererCmp{};

	bool hasTransform = false;
	TransformComponent transformCmp{};

	bool hasCollider = false;
	ColliderComponent colliderCmp{};

	bool hasScript = false;
	std::string behaviourName;//link to registry

};


struct SceneSnapshot {
	std::vector<EntitySnapshot> entities;
	std::string sceneLogicName;
};