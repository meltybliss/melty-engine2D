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


const char* EntityManager::GetName(int entity) const {
	if (entity < 0 || entity >= isAlive.size()) return;

	return entity_to_name[entity];
}

const char* EntityManager::GetTag(int entity) const {
	if (entity < 0 || entity >= isAlive.size()) return;

	return entity_to_tag[entity];
}

void EntityManager::SetName(int entity, char* name) {
	if (name_to_entity.find(name) != name_to_entity.end()) return;

	char* previous = entity_to_name[entity];
	name_to_entity.erase(previous);

	name_to_entity[name] = entity;
	entity_to_name[entity] = name;
}


void EntityManager::SetTag(int entity, char* tag) {

	char* previous = entity_to_tag[entity];
	auto range = tag_to_entity.equal_range(previous);

	for (auto it = range.first; it != range.second; it++) {
		if (it->second == entity) {
			tag_to_entity.erase(it);
			break;
		}
	}

	tag_to_entity.insert({ tag, entity });
	entity_to_tag[entity] = tag;
}


std::optional<int> EntityManager::GetEntityFromName(char* name) {
	auto it = name_to_entity.find(name);
	if (it == name_to_entity.end()) return std::nullopt;

	return it->second;
}

