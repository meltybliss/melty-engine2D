#pragma once

#include <string>

#include "engine/EntityManager.h"
#include "engine/Vec2.h"
#include "engine/Color.h"
#include "engine/RendererComp.h"
#include "engine/TransformComp.h"
#include "engine/ColliderComp.h"
#include "engine/CollisionSystem.h"
#include "engine/TextureAPI.h"

class SceneContext {
public:
    SceneContext(EntityManager& em, CollisionSystem& collisionSystem)
        : em(em), collisionSystem(collisionSystem) {
    }

    int CreateRectEntity(
        const Vec2& pos,
        float w,
        float h,
        const Color3& color,
        int layer
    ) {
        int e = em.CreateEntity();

        auto& rd = em.AddComponent<RendererComponent>(e);
        rd.visible = true;
        rd.kind = RenderKind::Shape;
        rd.type = ShapeType::Rect;
        rd.data.rect.width = w;
        rd.data.rect.height = h;
        rd.color = color;
        rd.layer = layer;

        auto& tr = em.AddComponent<TransformComponent>(e);
        tr.position = pos;

        return e;
    }

    int CreateSpriteEntity(
        const std::string& texturePath,
        const Vec2& pos,
        int layer
    ) {
        int e = em.CreateEntity();

        auto& rd = em.AddComponent<RendererComponent>(e);
        rd.visible = true;
        rd.kind = RenderKind::Sprite;
        rd.sprite.texturePath = texturePath;
        rd.sprite.texture = GetTexture(texturePath);
        rd.layer = layer;

        auto& tr = em.AddComponent<TransformComponent>(e);
        tr.position = pos;

        return e;
    }

    int CreateRectEntityWithCollider(
        const Vec2& pos,
        float w,
        float h,
        const Color3& color,
        int layer,
        bool isTrigger,
        bool isStatic
    ) {
        int e = CreateRectEntity(pos, w, h, color, layer);

        auto& col = em.AddComponent<ColliderComponent>(e);
        col.width = w;
        col.height = h;
        col.offset = { 0.0f, 0.0f };
        col.isTrigger = isTrigger;
        col.isStatic = isStatic;

        return e;
    }

    CollisionSystem& Collisions() {
        return collisionSystem;
    }

    EntityManager& Entities() {
        return em;
    }

private:
    EntityManager& em;
    CollisionSystem& collisionSystem;
};