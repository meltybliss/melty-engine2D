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
            if (!hasBegunPlay) {
                sceneLogic->BeginPlay();
                hasBegunPlay = true;
            }

            sceneLogic->Tick(dt);
        }
        
        scriptSystem.Tick(entityManager, dt);

        Tick(dt);

    }
    void Render() override;

    EntityManager& GetEntityManager() { return entityManager; }
    const EntityManager& GetEntityManager() const { return entityManager; }

    int AddRectEntity(const Vec2& pos, float w, float h, const Color3& color, int layer) {
        return CreateRectEntity(pos, w, h, color, layer);
    }

    int AddSpriteEntity(const std::string& texturePath, const Vec2& pos, int layer) {
        return CreateSpriteEntity(texturePath, pos, layer);
    }


    void StopPlay() {
        hasBegunPlay = false;

        auto alive = entityManager.GetAliveEntities();
        for (int e : alive) {
            if (!entityManager.HasComponent<ScriptComponent>(e)) continue;

            auto& sc = entityManager.GetComponent<ScriptComponent>(e);
            sc.started = false;
        }
    }


    SceneLogic* GetSceneLogic() const { return sceneLogic.get(); }


    void SetSceneLogic(std::unique_ptr<SceneLogic> newLogic) {
        sceneLogic = std::move(newLogic);

        if (sceneLogic) {
            sceneLogic->Bind(&entityManager);
        }
    }

protected:
    int CreateRectEntity(const Vec2& pos, float w, float h, const Color3& color, int layer);
    int CreateSpriteEntity(const std::string& texturePath, const Vec2& pos, int layer);

    virtual void Tick(float dt) {};

  


    EntityManager entityManager;
    ScriptSystem scriptSystem;
    std::unique_ptr<SceneLogic> sceneLogic;
private:

    RenderSystem renderSystem;
    
    bool hasBegunPlay = false;

};