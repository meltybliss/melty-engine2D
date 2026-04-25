#pragma once
#include <string>
#include "ICommand.h"
#include "engine/EntityManager.h"

class RenameEntityCommand : public ICommand {
public:
    RenameEntityCommand(EntityManager& em, int entity, std::string oldName, std::string newName)
        : em(em), entity(entity), oldName(std::move(oldName)), newName(std::move(newName)) {
    }

    void Execute() override {
        em.SetName(entity, newName);
    }

    void Undo() override {
        em.SetName(entity, oldName);
    }

private:
    EntityManager& em;
    int entity = -1;
    std::string oldName;
    std::string newName;
};