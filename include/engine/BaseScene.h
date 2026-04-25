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

protected:
    int CreateRectEntity(const Vec2& pos, float w, float h, const Color3& color, int layer);
    int CreateSpriteEntity(const std::string& texturePath, const Vec2& pos, int layer);


    EntityManager entityManager;
private:

    RenderSystem renderSystem;

};