#pragma once
#include <vector>
#include "EntityManager.h"
#include <memory>

class IScene {
public:
	virtual ~IScene() = default;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Tick(float dt) = 0;
	virtual void Render() = 0;


protected:

	EntityManager entityManager;

private:


};