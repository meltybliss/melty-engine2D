#pragma once
#include <unordered_map>
#include <functional>
#include <memory>
#include <string>
#include "Behaviour.h"


using Factory = std::function<std::unique_ptr<Behaviour>()>;

class BehaviourRegistry {
public:

	static BehaviourRegistry& Get() {//singleton
		static BehaviourRegistry instance;
		return  instance;
	}


	template<typename T>
	void Register(const std::string& name) {
		static_assert(std::is_base_of_v<Behaviour, T>, "T must derive from Behaviour");
		static_assert(std::is_default_constructible_v<T>, "T must be default constructible");

		factories[name] = [] {
			return std::make_unique<T>();
		};

	}

	std::unique_ptr<Behaviour> Create(const std::string&);


private:
	std::unordered_map<std::string, Factory> factories;
};