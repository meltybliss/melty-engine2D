#include "engine/ScriptSystem.h"


void ScriptSystem::Tick(EntityManager& em, float dt) {

	auto alive = em.GetAliveEntities();
	for (auto& i : alive) {
		if (em.IsAlive(i) == 0) continue;
		if (!em.HasComponent<ScriptComponent>(i)) continue;

		auto& sc = em.GetComponent<ScriptComponent>(i);
		auto& behaivor = sc.behaivor;
	
		if (!behaivor) continue;

		if (!sc.started) {
			sc.started = true;
			behaivor->Bind(&em, i);
			behaivor->BeginPlay();
		}


		behaivor->Tick(dt);
	}



}