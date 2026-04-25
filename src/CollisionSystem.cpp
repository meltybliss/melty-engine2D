#include "CollisionSystem.h"


void CollisionSystem::Tick(EntityManager& em) {
	int count = em.GetAllEntitiesCount();
	for (size_t i = 0; i < count; i++) {
		if (em.IsAlive(i) == 0) continue;
		if (!em.HasComponent<TransformComponent>(i)) continue;
		if (!em.HasComponent<ColliderComponent>(i)) continue;


		AABB box1 = MakeAABB(em, i);
	

		for (int j = i + 1; j < count; j++) {
			if (em.IsAlive(j) == 0) continue;
			if (!em.HasComponent<TransformComponent>(j)) continue;
			if (!em.HasComponent<ColliderComponent>(j)) continue;

			AABB box2 = MakeAABB(em, j);
			

			if (CheckOverlap(box1, box2)) {

				auto& col1 = em.GetComponent<ColliderComponent>(i);
				auto& col2 = em.GetComponent<ColliderComponent>(j);

				if (col1.isTrigger || col2.isTrigger) {

				}
				else {
					float overlapX = std::min(box1.max.x, box2.max.x) - std::max(box1.min.x, box2.min.x);
					float overlapY = std::min(box1.max.y, box2.max.y) - std::max(box1.min.y, box2.min.y);

					auto& tr1 = em.GetComponent<TransformComponent>(i);

					float center1X = (box1.min.x + box1.max.x) * 0.5f;
					float center2X = (box2.min.x + box2.max.x) * 0.5f;
					float center1Y = (box1.min.y + box1.max.y) * 0.5f;
					float center2Y = (box2.min.y + box2.max.y) * 0.5f;

					if (overlapX < overlapY) {
						if (center1X < center2X) tr1.position.x -= overlapX;
						else                     tr1.position.x += overlapX;
					}
					else {
						if (center1Y < center2Y) tr1.position.y -= overlapY;
						else                     tr1.position.y += overlapY;
					}
				}
			}
		}


	}
}

AABB CollisionSystem::MakeAABB(EntityManager& em, int entity) {
	auto& tr = em.GetComponent<TransformComponent>(entity);
	auto& cl = em.GetComponent<ColliderComponent>(entity);

	AABB box;

	float baseX = tr.position.x + cl.offset.x;
	float baseY = tr.position.y + cl.offset.y;
	box.min = Vec2{ baseX, baseY - cl.height };
	box.max = Vec2{ baseX + cl.width, baseY };


	return box;
}


bool CollisionSystem::CheckOverlap(const AABB& a, const AABB& b) {

	return a.min.x > b.max.x &&
		a.max.x > b.min.x &&
		a.min.y > b.max.y &&
		a.max.y > b.min.y;

}