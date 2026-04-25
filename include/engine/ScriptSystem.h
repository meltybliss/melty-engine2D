#pragma once

#include "Behaviour.h"
#include "EntityManager.h"
#include <memory>


class ScriptSystem {
public:

	void Tick(EntityManager& em, float dt);

private:

};