#pragma once
#include "Component.h"
#include "Transform.h"
#include <memory>
#include <vector>

class GameObject {
public:

	bool active = true;
	Transform transform;

	void AddComp(const std::unique_ptr<Component> comp) {
		components.push_back(std::move(comp));
	}
private:


	int id = 0;
	std::vector<std::unique_ptr<Component>> components;


};
