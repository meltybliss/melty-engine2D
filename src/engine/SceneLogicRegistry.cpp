#include "engine/SceneLogicRegistry.h"


std::unique_ptr<SceneLogic> SceneLogicRegister::Create(const std::string& name) {
	auto it = factories.find(name);
	if (it == factories.end()) return nullptr;

	return it->second();
}