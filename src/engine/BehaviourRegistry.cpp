#include "engine/BehaviourRegistry.h"


std::unique_ptr<Behaviour> BehaviourRegistry::Create(const std::string& name) {
	auto it = factories.find(name);
	if (it == factories.end()) return nullptr;

	return it->second();
}