#pragma once

#include "Behaviour.h"
#include "EntityManager.h"
#include "SceneContext.h"
#include <memory>


class ScriptSystem {
public:

	void Tick(EntityManager& em, SceneContext& ctx, float dt);

private:

};