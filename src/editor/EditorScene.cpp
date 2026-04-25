#include "editor/EditorScene.h"
#include "imgui/imgui.h"
#include "editor/RenameEntityCommand.h"
#include "editor/EditTransformCommand.h"
#include "editor/AddComponentCommand.h"
#include "engine/TransformComp.h"
#include "engine/RendererComp.h"
#include "engine/ColliderComp.h"
#include "engine/TextureAPI.h"

void EditorScene::Enter() {
    selectedEntity = -1;
    editingName.clear();
    wasEditingTransform = false;

    int e = CreateRectEntity({ 100.0f, 100.0f }, 80.0f, 80.0f, { 1.0f, 0.0f, 0.0f }, 0);
    entityManager.SetName(e, "Rect 1");
    selectedEntity = e;
    editingName = entityManager.GetName(e);
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

    if (ImGui::Button("Add Empty")) {
        int e = entityManager.CreateEntity();
        entityManager.AddComponent<TransformComponent>(e);
        entityManager.SetName(e, "Empty " + std::to_string(e));

        selectedEntity = e;
        editingName = entityManager.GetName(e);
    }

    if (ImGui::Button("Add Rect")) {
        int e = CreateRectEntity({ 100.0f, 100.0f }, 80.0f, 80.0f, { 0.2f, 0.8f, 0.3f }, 0);
        entityManager.SetName(e, "Rect " + std::to_string(e));

        selectedEntity = e;
        editingName = entityManager.GetName(e);
    }

    char spritePathBuf[256]{};
    std::snprintf(spritePathBuf, sizeof(spritePathBuf), "%s", newSpritePath.c_str());

    if (ImGui::InputText("New Sprite Path", spritePathBuf, sizeof(spritePathBuf))) {
        newSpritePath = spritePathBuf;
    }

    if (ImGui::Button("Add Sprite")) {
        int e = CreateSpriteEntity(newSpritePath, { 100.0f, 100.0f }, 0);

        if (e != -1) {
            entityManager.SetName(e, "Sprite " + std::to_string(e));
            selectedEntity = e;
            editingName = entityManager.GetName(e);
        }
    }


    ImGui::Separator();

    auto alive = entityManager.GetAliveEntities();
    for (int e : alive) {
        std::string label = entityManager.GetName(e);
        if (label.empty()) {
            label = "Entity " + std::to_string(e);
        }

        if (ImGui::Selectable(label.c_str(), selectedEntity == e)) {
            selectedEntity = e;
            editingName = entityManager.GetName(e);

            if (entityManager.HasComponent<RendererComponent>(e)) {
                auto& rd = entityManager.GetComponent<RendererComponent>(e);
                if (rd.kind == RenderKind::Sprite) {
                    editingTexturePath = rd.sprite.texturePath;
                }
                else {
                    editingTexturePath.clear();
                }
            }
            else {
                editingTexturePath.clear();
            }
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

        ImGui::Separator();
        ImGui::Text("Transform");

        TransformComponent oldValue = tr;

        float pos[2] = { tr.position.x, tr.position.y };
        float scale[2] = { tr.Scale.x, tr.Scale.y };
        float rotation = tr.rotation;

        if (ImGui::DragFloat2("Position", pos, 1.0f)) {
            tr.position.x = pos[0];
            tr.position.y = pos[1];
        }

        if (ImGui::DragFloat2("Scale", scale, 0.1f)) {
            tr.Scale.x = scale[0];
            tr.Scale.y = scale[1];
        }

        if (ImGui::DragFloat("Rotation", &rotation, 1.0f)) {
            tr.rotation = rotation;
        }

        if (ImGui::IsItemDeactivatedAfterEdit()) {
            TransformComponent newValue = tr;

            bool changed =
                oldValue.position.x != newValue.position.x ||
                oldValue.position.y != newValue.position.y ||
                oldValue.Scale.x != newValue.Scale.x ||
                oldValue.Scale.y != newValue.Scale.y ||
                oldValue.rotation != newValue.rotation;

            if (changed) {
                tr = oldValue;

                commandStack.Do(std::make_unique<EditTransformCommand>(
                    entityManager, selectedEntity, oldValue, newValue
                ));
            }
        }

        if (ImGui::Button("Remove Transform")) {
            entityManager.RemoveComponent<TransformComponent>(selectedEntity);
        }
    }

    // renderer
    if (entityManager.HasComponent<RendererComponent>(selectedEntity)) {
        auto& rd = entityManager.GetComponent<RendererComponent>(selectedEntity);

        ImGui::Separator();
        ImGui::Text("Renderer");

        ImGui::Checkbox("Visible", &rd.visible);
        ImGui::DragInt("Layer", &rd.layer, 1);

        if (rd.kind == RenderKind::Sprite) {
            char pathBuffer[256]{};
            std::snprintf(pathBuffer, sizeof(pathBuffer), "%s", editingTexturePath.c_str());

            if (ImGui::InputText("Texture Path", pathBuffer, sizeof(pathBuffer))) {
                editingTexturePath = pathBuffer;
            }

            if (ImGui::Button("Apply Texture")) {
                rd.sprite.texturePath = editingTexturePath;
                rd.sprite.texture = GetTexture(editingTexturePath);
            }
        }

        if (ImGui::Button("Remove Renderer")) {
            entityManager.RemoveComponent<RendererComponent>(selectedEntity);
            editingTexturePath.clear();
        }
    }
    else {
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
    if (entityManager.HasComponent<ColliderComponent>(selectedEntity)) {
        auto& cl = entityManager.GetComponent<ColliderComponent>(selectedEntity);

        ImGui::Separator();
        ImGui::Text("Collider");

        ImGui::DragFloat("Width", &cl.width, 1.0f, 0.0f);
        ImGui::DragFloat("Height", &cl.height, 1.0f, 0.0f);
        ImGui::Checkbox("Is Trigger", &cl.isTrigger);

        if (ImGui::Button("Remove Collider")) {
            entityManager.RemoveComponent<ColliderComponent>(selectedEntity);
        }
    }
    else {
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