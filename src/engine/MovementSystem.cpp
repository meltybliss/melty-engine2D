#include "engine/MovementSystem.h"
#include "engine/EntityManager.h"

void MovementSystem::Tick(EntityManager& em, float dt) {
	auto alive = em.GetAliveEntities();
	for (auto& i : alive) {
		if (em.IsAlive(i) == 0) continue;
		if (!em.HasComponent<VelocityComponent>(i)) continue;
		if (!em.HasComponent<TransformComponent>(i)) continue;

		auto& vel = em.GetComponent<VelocityComponent>(i);
		auto& tr = em.GetComponent<TransformComponent>(i);

		tr.position.x += vel.velocity.x * dt;
		tr.position.y += vel.velocity.y * dt;

	}


}