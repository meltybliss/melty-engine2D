#pragma once
#include <unordered_map>
#include <functional>
#include <memory>
#include <string>
#include "engine/SceneLogic.h"

using Factory = std::function<std::unique_ptr<SceneLogic>()>;

class SceneLogicRegister {
public:

	static SceneLogicRegister& Get() {//singleton
		static SceneLogicRegister instance;
		return instance;
	}

	template<typename T>
	void Register(const std::string& name) {
		static_assert(std::is_base_of_v<SceneLogic, T>, "T must derive from SceneLogic");
		static_assert(std::is_default_constructible_v<T>, "T must be default constructible");

		factories[name] = [] {
			return std::make_unique<T>();
		};
	}

	std::unique_ptr<SceneLogic> Create(const std::string& name);

private:

	std::unordered_map<std::string, Factory> factories;
};