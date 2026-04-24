#pragma once
#include "Component.h"
#include "RendererComp.h"
#include "TransformComp.h"
#include <vector>
#include <unordered_map>
#include <stdint.h>
#include <string>
#include <optional>

enum class ComponentBit {

	NONE = 0,
	RENDERER = 1ULL << 0,
	TRANSFORM = 1ULL << 1,

};



class EntityManager {
public:

	void Tick(float dt);

	int CreateEntity();
	void DestroyEntity(int entity);

	void AddRenderer(int entity);
	void AddTransform(int entity);

	RendererComponent& GetRenderer(int entity);
	TransformComponent& GetTransform(int entity);
	
	int GetAllEntitiesCount() const;
	uint8_t IsAlive(int entity) const {
		return isAlive[entity];
	}

	bool HasTransform(int entity) const {
		if (entity < 0 || entity >= entity_to_mask.size()) return false;

		const uint64_t mask = entity_to_mask[entity];
		const uint64_t target = static_cast<uint64_t>(ComponentBit::TRANSFORM);

		return (mask & target) == target;
	}

	bool HasRenderer(int entity) const {
		if (entity < 0 || entity >= entity_to_mask.size()) return false;

		const uint64_t mask = entity_to_mask[entity];
		const uint64_t target = static_cast<uint64_t>(ComponentBit::RENDERER);

		return (mask & target) == target;
	}

	const std::string& GetName(int entity) const;
	const std::string& GetTag(int entity) const;

	std::optional<int> GetEntityFromName(const std::string&);

	void SetName(int entity, const std::string& name);
	void SetTag(int entity, const std::string& tag);
private:


	std::vector<uint64_t> entity_to_mask;//[entityID] = bit
	std::vector<uint8_t> isAlive;//[entityID] = 0 or 1; 0 = dead

	std::vector<std::string> entity_to_name;
	std::vector<std::string> entity_to_tag;

	std::unordered_map<std::string, int> name_to_entity;
	std::unordered_multimap<std::string, int> tag_to_entity;


	std::vector<int> entity_to_renderer_idx;
	std::vector<int> entity_to_transform_idx;

	std::vector<RendererComponent> rendererComps;
	std::vector<TransformComponent> transforms;

	int nextEntityId = 0;
	int entitiesCount = 0;

};

