#pragma once
#include "Vec2.h"
#include "Component.h"

class TransformComponent : public Component {
public:
	Vec2 position{};
	Vec2 Scale{};
	float rotation = 0.0f;

};