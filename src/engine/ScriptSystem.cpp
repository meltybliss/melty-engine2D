#include "engine/ScriptSystem.h"


void ScriptSystem::Tick(EntityManager& em, float dt) {

	auto alive = em.GetAliveEntities();
	for (auto& i : alive) {
		if (em.IsAlive(i) == 0) continue;
		if (!em.HasComponent<ScriptComponent>(i)) continue;

		auto& sc = em.GetComponent<ScriptComponent>(i);
		auto& behaviour = sc.behaviour;
	
		if (!behaviour) continue;

		if (!sc.started) {
			sc.started = true;
			behaviour->Bind(&em, i);
			behaviour->BeginPlay();
		}


		behaviour->Tick(dt);
	}



}