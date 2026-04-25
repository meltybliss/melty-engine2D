#pragma once
#include "Vec2.h"
#include "Component.h"

class ColliderComponent : public Component {
public:
	float width = 0.0f;
	float height = 0.0f;

	Vec2 offset{};
	bool isTrigger = false;//if true, it would be detected but not be hitted

};