#include "editor/EditorScene.h"
#include "imgui/imgui.h"
#include "editor/RenameEntityCommand.h"
#include "editor/MoveEntityCommand.h"
#include "editor/AddComponentCommand.h"
#include "engine/TransformComp.h"
#include "engine/RendererComp.h"
#include "engine/ColliderComp.h"

void EditorScene::Enter() {
    selectedEntity = -1;
    editingName.clear();
    wasEditingTransform = false;
}

void EditorScene::Exit() {
}

void EditorScene::Tick(float dt) {
}

void EditorScene::Render() {
    BaseScene::Render();

    DrawHierarchy();
    DrawInspector();
}

void EditorScene::DrawHierarchy() {
    ImGui::Begin("Hierarchy");

    auto alive = entityManager.GetAliveEntities();
    for (int e : alive) {
        std::string label = entityManager.GetName(e);
        if (label.empty()) {
            label = "Entity " + std::to_string(e);
        }

        bool selected = (selectedEntity == e);
        if (ImGui::Selectable(label.c_str(), selected)) {
            selectedEntity = e;
            editingName = entityManager.GetName(e);
        }
    }

    ImGui::End();
}

void EditorScene::DrawInspector() {
    ImGui::Begin("Inspector");

    if (selectedEntity == -1 || !entityManager.IsAlive(selectedEntity)) {
        ImGui::Text("No entity selected");
        ImGui::End();
        return;
    }

    ImGui::Text("Entity: %d", selectedEntity);

    // name
    char buf[256]{};
    std::snprintf(buf, sizeof(buf), "%s", editingName.c_str());

    if (ImGui::InputText("Name", buf, sizeof(buf))) {
        editingName = buf;
    }

    if (ImGui::IsItemDeactivatedAfterEdit()) {
        std::string oldName = entityManager.GetName(selectedEntity);
        std::string newName = editingName;

        if (oldName != newName) {
            commandStack.Do(std::make_unique<RenameEntityCommand>(
                entityManager, selectedEntity, oldName, newName
            ));
        }
    }

    // transform
    if (entityManager.HasComponent<TransformComponent>(selectedEntity)) {
        auto& tr = entityManager.GetComponent<TransformComponent>(selectedEntity);

        float pos[2] = { tr.position.x, tr.position.y };

        if (ImGui::IsItemActivated()) {
            oldTransformPos = tr.position;
            wasEditingTransform = true;
        }

        if (ImGui::DragFloat2("Position", pos, 1.0f)) {
            tr.position.x = pos[0];
            tr.position.y = pos[1];
        }

        if (ImGui::IsItemActivated()) {
            oldTransformPos = tr.position;
            wasEditingTransform = true;
        }

        if (ImGui::IsItemDeactivatedAfterEdit()) {
            Vec2 newPos = tr.position;

            if (wasEditingTransform &&
                (newPos.x != oldTransformPos.x || newPos.y != oldTransformPos.y)) {

                tr.position = oldTransformPos;

                commandStack.Do(std::make_unique<MoveEntityCommand>(
                    entityManager, selectedEntity, oldTransformPos, newPos
                ));
            }

            wasEditingTransform = false;
        }
    }
    else {
        if (ImGui::Button("Add Transform")) {
            commandStack.Do(
                std::make_unique<AddComponentCommand<TransformComponent>>(
                    entityManager, selectedEntity, TransformComponent{}
                )
            );
        }
    }

    // renderer
    if (!entityManager.HasComponent<RendererComponent>(selectedEntity)) {
        if (ImGui::Button("Add Renderer")) {
            RendererComponent rd{};
            rd.visible = true;

            commandStack.Do(
                std::make_unique<AddComponentCommand<RendererComponent>>(
                    entityManager, selectedEntity, rd
                )
            );
        }
    }

    // collider
    if (!entityManager.HasComponent<ColliderComponent>(selectedEntity)) {
        if (ImGui::Button("Add Collider")) {
            ColliderComponent cl{};
            cl.width = 32.0f;
            cl.height = 32.0f;

            commandStack.Do(
                std::make_unique<AddComponentCommand<ColliderComponent>>(
                    entityManager, selectedEntity, cl
                )
            );
        }
    }

    ImGui::End();
}