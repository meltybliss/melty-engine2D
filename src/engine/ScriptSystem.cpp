#include "engine/ScriptSystem.h"


void ScriptSystem::Tick(EntityManager& em, SceneContext& ctx, float dt) {

	auto alive = em.GetAliveEntities();
	for (auto& i : alive) {
		if (em.IsAlive(i) == 0) continue;
		if (!em.HasComponent<ScriptComponent>(i)) continue;

		auto& sc = em.GetComponent<ScriptComponent>(i);
		auto& behaviour = sc.behaviour;
	
		if (!behaviour) continue;

		if (!sc.started) {
			sc.started = true;
			behaviour->Bind(&em, &ctx, i);
			behaviour->BeginPlay();
		}


		behaviour->Tick(dt);
	}



}