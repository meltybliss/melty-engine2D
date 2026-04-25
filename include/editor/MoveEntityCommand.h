#pragma once
#include "ICommand.h"
#include "engine/EntityManager.h"
#include "engine/TransformComp.h"

class MoveEntityCommand : public ICommand {
public:
    MoveEntityCommand(EntityManager& em, int entity, Vec2 oldPos, Vec2 newPos)
        : em(em), entity(entity), oldPos(oldPos), newPos(newPos) {
    }

    void Execute() override {
        if (!em.IsAlive(entity)) return;
        if (!em.HasComponent<TransformComponent>(entity)) return;

        em.GetComponent<TransformComponent>(entity).position = newPos;
    }

    void Undo() override {
        if (!em.IsAlive(entity)) return;
        if (!em.HasComponent<TransformComponent>(entity)) return;

        em.GetComponent<TransformComponent>(entity).position = oldPos;
    }

private:
    EntityManager& em;
    int entity = -1;
    Vec2 oldPos{};
    Vec2 newPos{};
};