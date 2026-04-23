#pragma once
#include <vector>
#include "EntityManager.h"
#include <memory>

class IScene {
public:
	virtual ~IScene() = default;
	virtual void Tick(float dt) = 0;
	virtual void Render() = 0;


private:

	EntityManager manager;

};