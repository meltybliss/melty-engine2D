#pragma once
#include "EntityManager.h"

struct AABB {
	Vec2 min{};
	Vec2 max{};

};

class CollisionSystem {
public:

	void Tick(EntityManager& em);
	bool IsOverlapping(EntityManager& em, int a, int b);
private:
	AABB MakeAABB(EntityManager& em, int entity);
	bool CheckOverlap(const AABB& a, const AABB& b);
	

	void ResolveCollision(
		EntityManager& em,
		int a,
		int b,
		const AABB& boxA,
		const AABB& boxB
	);
};