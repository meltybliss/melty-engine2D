#pragma once


class Component {
public:
	virtual ~Component();

	virtual void Tick(float dt) = 0;

	bool active = true;

protected:
	//GameObject* owner
};