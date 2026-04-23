#pragma once
#include "IScene.h"
#include "EntityManager.h"
#include "RenderSystem.h"

class BaseScene : public IScene {
public:
	virtual ~BaseScene() override = default;

    void Enter() override {}
    void Exit() override {}
    void Tick(float dt) override {}
    void Render() override;


private:

    EntityManager entityManager;
    RenderSystem renderSystem;

};