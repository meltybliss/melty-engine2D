#pragma once
#include "Component.h"
#include "RendererComp.h"
#include "TransformComp.h"
#include <vector>
#include <stdint.h>

enum class ComponentBit {

	NONE = 0,
	RENDERER = 1ULL << 1,
	TRANSFORM = 1ULL << 2,

};


class EntityManager {
public:

	void Tick(float dt);

	void CreateEntity();

private:

	std::vector<int> entity_to_index;//[entityID] = index
	std::vector<uint64_t> entity_to_mask;//[entityID] = bit
	std::vector<uint8_t> isAlive;//[entityID] = 0 or 1; 0 = dead

	std::vector<RendererComponent> rendererComps;
	std::vector<TransformComponent> transforms;
};

