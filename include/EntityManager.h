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


inline uint64_t operator|=(uint64_t& baseBit, const ComponentBit& addition) {
	return static_cast<uint64_t>(baseBit |= static_cast<uint64_t>(addition));
}


class EntityManager {
public:

	void Tick(float dt);

	int CreateEntity();
	void AddRenderer(int entity);
	void AddTransform(int entity);

	RendererComponent& GetRenderer(int entity);
	TransformComponent& GetTransform(int entity);

private:


	std::vector<uint64_t> entity_to_mask;//[entityID] = bit
	std::vector<uint8_t> isAlive;//[entityID] = 0 or 1; 0 = dead

	std::vector<int> entity_to_renderer_idx;
	std::vector<int> entity_to_transform_idx;

	std::vector<RendererComponent> rendererComps;
	std::vector<TransformComponent> transforms;

	int nextEntityId = 0;

};

