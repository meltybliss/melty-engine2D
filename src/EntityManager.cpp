#include "EntityManager.h"

int EntityManager::CreateEntity() {
	int id = nextEntityId;

	if (entity_to_renderer_idx.size() <= id) entity_to_renderer_idx.resize(id + 1, -1);
	if (entity_to_transform_idx.size() <= id) entity_to_transform_idx.resize(id + 1, -1);

	entity_to_mask.push_back(0);
	isAlive.push_back(1);

	entitiesCount++;

	nextEntityId++;
	return id;

}



void EntityManager::AddRenderer(int entity) {
	if (entity_to_renderer_idx[entity] != -1) return;

	RendererComponent cmp{};
	cmp.visible = true;
	
	rendererComps.push_back(cmp);
	
	entity_to_renderer_idx[entity] = rendererComps.size() - 1;

	entity_to_mask[entity] |= static_cast<uint64_t>(ComponentBit::RENDERER);
}


void EntityManager::AddTransform(int entity) {
	if (entity_to_transform_idx[entity] != -1) return;

	TransformComponent cmp{};
	
	transforms.push_back(cmp);

	entity_to_transform_idx[entity] = transforms.size() - 1;
	
	entity_to_mask[entity] |= static_cast<uint64_t>(ComponentBit::TRANSFORM);
}


RendererComponent& EntityManager::GetRenderer(int entity) {
	return rendererComps[entity_to_renderer_idx[entity]];
}


TransformComponent& EntityManager::GetTransform(int entity) {
	return transforms[entity_to_transform_idx[entity]];
}



int EntityManager::GetAllEntitiesCount() const {
	return entitiesCount;
}