#pragma once
#include "ICommand.h"
#include "engine/EntityManager.h"
#include "engine/TransformComp.h"

class EditTransformCommand : public ICommand {
public:
    EditTransformCommand(EntityManager& em, int entity,
        const TransformComponent& oldValue,
        const TransformComponent& newValue)
        : em(em), entity(entity), oldValue(oldValue), newValue(newValue) {
    }

    void Execute() override {
        if (!em.IsAlive(entity)) return;
        if (!em.HasComponent<TransformComponent>(entity)) return;

        em.GetComponent<TransformComponent>(entity) = newValue;
    }

    void Undo() override {
        if (!em.IsAlive(entity)) return;
        if (!em.HasComponent<TransformComponent>(entity)) return;

        em.GetComponent<TransformComponent>(entity) = oldValue;
    }

private:
    EntityManager& em;
    int entity = -1;
    TransformComponent oldValue{};
    TransformComponent newValue{};
};