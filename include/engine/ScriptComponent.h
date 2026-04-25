#pragma once

#include "Component.h"
#include "Behaviour.h"
#include <memory>


class ScriptComponent : public Component {
public:

	std::unique_ptr<Behaviour> behaviour;
	bool started = false;

};