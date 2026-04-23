#include "EntityManager.h"

void EntityManager::CreateEntity() {

	PushEntity(nextEntityId);

	nextEntityId++;
}


void EntityManager::PushEntity(int id) {

	entity_to_mask.push_back(0ULL);
	isAlive.push_back(1);//alive


}


void EntityManager::AddRenderer(int entity) {
	RendererComponent cmp{};
	cmp.visible = true;
	
	if (entity_to_mask.size() > entity) {
		entity_to_mask[entity] |= ComponentBit::RENDERER;
	}
	else {
		entity_to_mask.resize(entity + 1);
		entity_to_mask[entity] = static_cast<uint64_t>(ComponentBit::RENDERER);
	}

	if (rendererComps.size() <= entity) {
		rendererComps.resize(entity + 1);
	}
	
	rendererComps[entity] = cmp;

}