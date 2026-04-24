#include "EntityManager.h"

int EntityManager::CreateEntity() {
	int id = nextEntityId;

	if (entity_to_renderer_idx.size() <= id) entity_to_renderer_idx.resize(id + 1, -1);
	if (entity_to_transform_idx.size() <= id) entity_to_transform_idx.resize(id + 1, -1);

	entity_to_mask.push_back(0);
	isAlive.push_back(1);

	entity_to_name.push_back("");
	entity_to_tag.push_back("");

	entitiesCount++;
	nextEntityId++;
	return id;
}


void EntityManager::DestroyEntity(int entity) {
	if (entity < 0 || entity >= static_cast<int>(isAlive.size())) return;
	if (!isAlive[entity]) return;

	isAlive[entity] = 0;
	entity_to_mask[entity] = 0;

	std::string name = entity_to_name[entity];
	if (!name.empty()) {
		name_to_entity.erase(name);
		entity_to_name[entity].clear();
	}

	std::string tag = entity_to_tag[entity];
	if (!tag.empty()) {
		auto range = tag_to_entity.equal_range(tag);
		for (auto it = range.first; it != range.second; ++it) {
			if (it->second == entity) {
				tag_to_entity.erase(it);
				break;
			}
		}
		entity_to_tag[entity].clear();
	}

	entity_to_renderer_idx[entity] = -1;
	entity_to_transform_idx[entity] = -1;
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


const std::string& EntityManager::GetName(int entity) const {
	static const std::string empty = "";
	if (entity < 0 || entity >= static_cast<int>(isAlive.size())) return empty;

	return entity_to_name[entity];
}

const std::string& EntityManager::GetTag(int entity) const {
	static const std::string empty = "";
	if (entity < 0 || entity >= static_cast<int>(isAlive.size())) return empty;

	return entity_to_tag[entity];
}

void EntityManager::SetName(int entity, const std::string& name) {
	if (entity < 0 || entity >= static_cast<int>(isAlive.size())) return;
	if (!isAlive[entity]) return;

	auto found = name_to_entity.find(name);
	if (found != name_to_entity.end() && found->second != entity) return;

	std::string previous = entity_to_name[entity];
	if (!previous.empty()) {
		name_to_entity.erase(previous);
	}

	entity_to_name[entity] = name;
	if (!name.empty()) {
		name_to_entity[name] = entity;
	}
}


void EntityManager::SetTag(int entity, const std::string& tag) {
	if (entity < 0 || entity >= static_cast<int>(isAlive.size())) return;
	if (!isAlive[entity]) return;

	std::string previous = entity_to_tag[entity];
	if (!previous.empty()) {
		auto range = tag_to_entity.equal_range(previous);

		for (auto it = range.first; it != range.second; ++it) {
			if (it->second == entity) {
				tag_to_entity.erase(it);
				break;
			}
		}
	}

	entity_to_tag[entity] = tag;

	if (!tag.empty()) {
		tag_to_entity.insert({ tag, entity });
	}
}

std::optional<int> EntityManager::GetEntityFromName(const std::string& name) {
	auto it = name_to_entity.find(name);
	if (it == name_to_entity.end()) return std::nullopt;

	return it->second;
}

