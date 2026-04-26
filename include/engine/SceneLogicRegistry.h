#pragma once
#include <unordered_map>
#include <functional>
#include <memory>
#include <string>
#include <typeindex>
#include <optional>
#include "engine/SceneLogic.h"


class SceneLogicRegister {
public:

	using Factory = std::function<std::unique_ptr<SceneLogic>()>;


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

		typeToName[std::type_index(typeid(T))] = name;
	}

	std::unique_ptr<SceneLogic> Create(const std::string& name);

	std::optional<std::string> GetName(const SceneLogic* base) const {
		if (!base) return std::nullopt;

		auto it = typeToName.find(std::type_index(typeid(*base)));
		if (it == typeToName.end()) return std::nullopt;

		return it->second;
	}



private:

	std::unordered_map<std::string, Factory> factories;
	std::unordered_map<std::type_index, std::string> typeToName;
};