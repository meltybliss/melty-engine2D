#pragma once

class IScene {
public:
	virtual ~IScene() = default;
	virtual void Tick(float dt) = 0;
	virtual void Render() = 0;

};