#include "engine/EntityManager.h"

int EntityManager::CreateEntity() {
	int id = nextEntityId;

	if (entity_to_renderer_idx.size() <= id) entity_to_renderer_idx.resize(id + 1, -1);
	if (entity_to_transform_idx.size() <= id) entity_to_transform_idx.resize(id + 1, -1);
	if (entity_to_collider_idx.size() <= id) entity_to_collider_idx.resize(id + 1, -1);
	if (entity_to_script_idx.size() <= id) entity_to_script_idx.resize(id + 1, -1);

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
	entity_to_collider_idx[entity] = -1;
	entity_to_script_idx[entity] = -1;
}

template<>
T& EntityManager::AddComponent<RendererComponent>(int entity) {
	if (entity_to_renderer_idx[entity] != -1) return;

	RendererComponent cmp{};
	cmp.visible = true;

	rendererComps.push_back(cmp);

	entity_to_renderer_idx[entity] = rendererComps.size() - 1;

	entity_to_mask[entity] |= static_cast<uint64_t>(ComponentBit::RENDERER);
}

template<>
TransformComponent& EntityManager::AddComponent<TransformComponent>(int entity) {
	if (entity_to_transform_idx[entity] != -1) return;

	TransformComponent cmp{};

	transforms.push_back(cmp);

	entity_to_transform_idx[entity] = transforms.size() - 1;
	entity_to_mask[entity] |= static_cast<uint64_t>(ComponentBit::TRANSFORM);
	return cmp;
}

template<>
ColliderComponent& EntityManager::AddComponent<ColliderComponent>(int entity) {
	if (entity_to_collider_idx[entity] != -1) return;

	ColliderComponent cmp{};

	colliders.push_back(cmp);

	entity_to_collider_idx[entity] = colliders.size() - 1;
	entity_to_mask[entity] |= static_cast<uint64_t>(ComponentBit::COLLIDER);
	return cmp;
}


template<>
ScriptComponent& EntityManager::AddComponent<ScriptComponent>(int entity) {
	if (entity_to_script_idx[entity] != -1) return;

	ScriptComponent cmp{};
	scripts.push_back(std::move(cmp));

	entity_to_script_idx[entity] = scripts.size() - 1;
	entity_to_mask[entity] |= static_cast<uint64_t>(ComponentBit::SCRIPT);
	return cmp;
}


template<>
void EntityManager::RemoveComponent<RendererComponent>(int entity) {
	if (entity < 0 || entity >= entity_to_renderer_idx.size()) return;

	int idx = entity_to_renderer_idx[entity];
	if (idx == -1) return;


	rendererComps[idx].active = false;
	entity_to_renderer_idx[entity] = -1;
	entity_to_mask[entity] &= ~static_cast<uint64_t>(ComponentBit::RENDERER);
}

template<>
void EntityManager::RemoveComponent<TransformComponent>(int entity) {
	if (entity < 0 || entity >= entity_to_transform_idx.size()) return;
	int idx = entity_to_transform_idx[entity];

	transforms[idx].active = false;
	entity_to_transform_idx[entity] = -1;
	entity_to_mask[entity] &= ~static_cast<uint64_t>(ComponentBit::TRANSFORM);
}

template<>
void EntityManager::RemoveComponent<ColliderComponent>(int entity) {
	if (entity < 0 || entity >= entity_to_collider_idx.size()) return;
	int idx = entity_to_collider_idx[entity];

	colliders[idx].active = false;
	entity_to_collider_idx[entity] = -1;
	entity_to_mask[entity] &= ~static_cast<uint64_t>(ComponentBit::COLLIDER);
}


template<>
void EntityManager::RemoveComponent<ScriptComponent>(int entity) {
	if (entity < 0 || entity >= entity_to_script_idx.size()) return;
	int idx = entity_to_script_idx[entity];

	scripts[idx].active = false;
	entity_to_script_idx[entity] = -1;
	entity_to_mask[entity] &= ~static_cast<uint64_t>(ComponentBit::SCRIPT);

}


template<>
RendererComponent& EntityManager::GetComponent<RendererComponent>(int entity) {
	return rendererComps[entity_to_renderer_idx[entity]];
}

template<>
TransformComponent& EntityManager::GetComponent<TransformComponent>(int entity) {
	return transforms[entity_to_transform_idx[entity]];
}

template<>
ColliderComponent& EntityManager::GetComponent<ColliderComponent>(int entity) {
	return colliders[entity_to_collider_idx[entity]];
}


template<>
ScriptComponent& EntityManager::GetComponent<ScriptComponent>(int entity) {
	return scripts[entity_to_script_idx[entity]];
}


template<>
bool EntityManager::HasComponent<RendererComponent>(int entity) const {
	if (entity < 0 || entity >= entity_to_mask.size()) return false;

	const uint64_t mask = entity_to_mask[entity];
	const uint64_t target = static_cast<uint64_t>(ComponentBit::RENDERER);

	return (mask & target) == target;
}


template<>
bool EntityManager::HasComponent<TransformComponent>(int entity) const {
	if (entity < 0 || entity >= entity_to_mask.size()) return false;

	const uint64_t mask = entity_to_mask[entity];
	const uint64_t target = static_cast<uint64_t>(ComponentBit::TRANSFORM);

	return (mask & target) == target;
}


template<>
bool EntityManager::HasComponent<ColliderComponent>(int entity) const {
	if (entity < 0 || entity >= entity_to_mask.size()) return false;

	const uint64_t mask = entity_to_mask[entity];
	const uint64_t target = static_cast<uint64_t>(ComponentBit::COLLIDER);

	return (mask & target) == target;
}


template<>
bool EntityManager::HasComponent<ScriptComponent>(int entity) const {
	if (entity < 0 || entity >= entity_to_mask.size()) return false;

	const uint64_t mask = entity_to_mask[entity];
	const uint64_t target = static_cast<uint64_t>(ComponentBit::SCRIPT);

	return (mask & target) == target;
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


std::vector<int> EntityManager::GetAliveEntities() const {
	std::vector<int> result;

	for (int i = 0; i < isAlive.size(); i++) {
		if (isAlive[i] == 0) continue;

		result.push_back(i);
	}

	return result;

}