#include "engine/CollisionSystem.h"


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
					ResolveCollision(em, i, j, box1, box2);
				}
			}
		}


	}
}

AABB CollisionSystem::MakeAABB(EntityManager& em, int entity) {
	auto& tr = em.GetComponent<TransformComponent>(entity);
	auto& cl = em.GetComponent<ColliderComponent>(entity);

	float centerX = tr.position.x + cl.offset.x;
	float centerY = tr.position.y + cl.offset.y;

	float halfW = cl.width * 0.5f;
	float halfH = cl.height * 0.5f;

	//center is the reference point
	AABB box;
	box.min = Vec2{ centerX - halfW, centerY - halfH };
	box.max = Vec2{ centerX + halfW, centerY + halfH };

	return box;
}

void CollisionSystem::ResolveCollision(
	EntityManager& em,
	int a,
	int b,
	const AABB& boxA,
	const AABB& boxB
) {
	auto& colA = em.GetComponent<ColliderComponent>(a);
	auto& colB = em.GetComponent<ColliderComponent>(b);

	if (colA.isStatic && colB.isStatic) return;

	float overlapX = std::min(boxA.max.x, boxB.max.x) - std::max(boxA.min.x, boxB.min.x);
	float overlapY = std::min(boxA.max.y, boxB.max.y) - std::max(boxA.min.y, boxB.min.y);

	float centerAX = (boxA.min.x + boxA.max.x) * 0.5f;
	float centerBX = (boxB.min.x + boxB.max.x) * 0.5f;
	float centerAY = (boxA.min.y + boxA.max.y) * 0.5f;
	float centerBY = (boxB.min.y + boxB.max.y) * 0.5f;

	Vec2 push{};

	if (overlapX < overlapY) {
		push.x = (centerAX < centerBX) ? -overlapX : overlapX;
	}
	else {
		push.y = (centerAY < centerBY) ? -overlapY : overlapY;
	}

	if (colA.isStatic && !colB.isStatic) {
		auto& trB = em.GetComponent<TransformComponent>(b);
		trB.position.x -= push.x;
		trB.position.y -= push.y;
	}
	else if (!colA.isStatic && colB.isStatic) {
		auto& trA = em.GetComponent<TransformComponent>(a);
		trA.position.x += push.x;
		trA.position.y += push.y;
	}
	else {
		auto& trA = em.GetComponent<TransformComponent>(a);
		auto& trB = em.GetComponent<TransformComponent>(b);

		trA.position.x += push.x * 0.5f;
		trA.position.y += push.y * 0.5f;

		trB.position.x -= push.x * 0.5f;
		trB.position.y -= push.y * 0.5f;
	}
}

bool CollisionSystem::CheckOverlap(const AABB& a, const AABB& b) {
	return a.min.x < b.max.x &&
		a.max.x > b.min.x &&
		a.min.y < b.max.y &&
		a.max.y > b.min.y;
}

bool CollisionSystem::IsOverlapping(EntityManager& em, int a, int b) {
	if (!em.IsAlive(a) || !em.IsAlive(b)) return false;
	if (!em.HasComponent<TransformComponent>(a)) return false;
	if (!em.HasComponent<TransformComponent>(b)) return false;
	if (!em.HasComponent<ColliderComponent>(a)) return false;
	if (!em.HasComponent<ColliderComponent>(b)) return false;

	AABB boxA = MakeAABB(em, a);
	AABB boxB = MakeAABB(em, b);

	return CheckOverlap(boxA, boxB);
}