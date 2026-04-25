#pragma once

#include "Component.h"
#include "Behaivor.h"
#include <memory>


class ScriptComponent : public Component {
public:

	std::unique_ptr<Behaivor> behaivor;
	bool started = false;

};