#pragma once
#include "EntityManager.h"

struct AABB {
	Vec2 min{};
	Vec2 max{};

};

class CollisionSystem {
public:

	void Tick(EntityManager& em);

private:
	AABB MakeAABB(EntityManager& em, int entity);
	bool CheckOverlap(const AABB& a, const AABB& b);
};