#pragma once
#include <vector>
#include "GameObject.h"
#include <memory>

class IScene {
public:
	virtual ~IScene() = default;
	virtual void Tick(float dt) = 0;
	virtual void Render() = 0;

	void AddObject(std::unique_ptr<GameObject> obj) {
		objects.push_back(std::move(obj));
	}

private:

	std::vector<std::unique_ptr<GameObject>> objects;
};