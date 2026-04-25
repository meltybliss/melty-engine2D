#pragma once
#include "IScene.h"
#include "EntityManager.h"
#include "ScriptSystem.h"
#include "SceneLogic.h"
#include "RenderSystem.h"

class BaseScene : public IScene {
public:
	virtual ~BaseScene() override = default;

    void Enter() override {}
    void Exit() override {}
    void MainTick(float dt) override final {
        if (sceneLogic) {
            sceneLogic->Tick(dt);
        }
        
        scriptSystem.Tick(entityManager, dt);

        Tick(dt);

    }
    void Render() override;

protected:
    int CreateRectEntity(const Vec2& pos, float w, float h, const Color3& color, int layer);
    int CreateSpriteEntity(const std::string& texturePath, const Vec2& pos, int layer);

    virtual void Tick(float dt);

    void SetSceneLogic(std::unique_ptr<SceneLogic> newLogic) {
        sceneLogic = std::move(newLogic);

        if (sceneLogic) {
            sceneLogic->Bind(&entityManager);
            sceneLogic->BeginPlay();
        }
    }

    EntityManager entityManager;
    ScriptSystem scriptSystem;
    std::unique_ptr<SceneLogic> sceneLogic;
private:

    RenderSystem renderSystem;

};