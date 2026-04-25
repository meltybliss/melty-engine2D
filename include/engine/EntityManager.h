#pragma once
#include "Component.h"
#include "RendererComp.h"
#include "TransformComp.h"
#include "ColliderComp.h"
#include "ScriptComponent.h"
#include <vector>
#include <unordered_map>
#include <stdint.h>
#include <string>
#include <optional>

enum class ComponentBit {

	NONE = 0,
	RENDERER = 1ULL << 0,
	TRANSFORM = 1ULL << 1,
	COLLIDER = 1ULL << 2,
	SCRIPT = 1ULL << 3,

};



class EntityManager {
public:

	void Tick(float dt);

	int CreateEntity();
	void DestroyEntity(int entity);

	template<typename T>
	void RemoveComponent(int entity);

	template<typename T>
	T& AddComponent(int entity);

	template<typename T>
	T& GetComponent(int entity);

	
	int GetAllEntitiesCount() const;
	uint8_t IsAlive(int entity) const {
		if (entity < 0 || entity >= (int)entity_to_mask.size()) return 0;
		return isAlive[entity];
	}


	template<typename T>
	bool HasComponent(int entity) const;

	const std::string& GetName(int entity) const;
	const std::string& GetTag(int entity) const;

	std::optional<int> GetEntityFromName(const std::string&);

	void SetName(int entity, const std::string& name);
	void SetTag(int entity, const std::string& tag);

	std::vector<int> GetAliveEntities() const;

	uint64_t GetEntityMask(int entity) const {
		if (entity < 0 || entity >= (int)entity_to_mask.size()) return 0ULL;

		return entity_to_mask[entity];

	}
private:


	std::vector<uint64_t> entity_to_mask;//[entityID] = bit
	std::vector<uint8_t> isAlive;//[entityID] = 0 or 1; 0 = dead

	std::vector<std::string> entity_to_name;
	std::vector<std::string> entity_to_tag;

	std::unordered_map<std::string, int> name_to_entity;
	std::unordered_multimap<std::string, int> tag_to_entity;


	std::vector<int> entity_to_renderer_idx;
	std::vector<int> entity_to_transform_idx;
	std::vector<int> entity_to_collider_idx;
	std::vector<int> entity_to_script_idx;

	std::vector<RendererComponent> rendererComps;
	std::vector<TransformComponent> transforms;
	std::vector<ColliderComponent> colliders;
	std::vector<ScriptComponent> scripts;


	int nextEntityId = 0;
	int entitiesCount = 0;

};

