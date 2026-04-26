#include "editor/EditorScene.h"
#include "imgui/imgui.h"
#include "editor/RenameEntityCommand.h"
#include "editor/EditTransformCommand.h"
#include "editor/AddComponentCommand.h"
#include "engine/TransformComp.h"
#include "engine/RendererComp.h"
#include "engine/ColliderComp.h"
#include "engine/TextureAPI.h"


EditorScene::EditorScene(std::unique_ptr<BaseScene> targetScene) :
    editingTarget(std::move(targetScene)) {

    playTarget = editingTarget
}

void EditorScene::Enter() {
    selectedEntity = -1;
    editingName.clear();
    /**wasEditingTransform = false;

    int e = CreateRectEntity({ 100.0f, 100.0f }, 80.0f, 80.0f, { 1.0f, 0.0f, 0.0f }, 0);
    entityManager.SetName(e, "Rect 1");
    selectedEntity = e;
    editingName = entityManager.GetName(e);**/

    editingTexturePath.clear();

    if (editingTarget) {
        editingTarget->Enter();
    }
}

void EditorScene::Exit() {
}

void EditorScene::Tick(float dt) {
    if (isPlaying && editingTarget) {
        editingTarget->MainTick(dt);
    }
}

void EditorScene::Render() {
    if (editingTarget) {
        editingTarget->Render();
    }


    DrawHierarchy();
    DrawInspector();
    DrawToolbar();
}


void EditorScene::DrawToolbar() {
    ImGui::Begin("Toolbar");

    if (!isPlaying) {
        if (ImGui::Button("Play")) {
            isPlaying = true;
        }
    }
    else {
        if (ImGui::Button("Stop")) {
            isPlaying = false;
            if (editingTarget) {
                editingTarget->StopPlay();
            }
        }
    }

    ImGui::End();
}

void EditorScene::DrawHierarchy() {
    if (!editingTarget) return;

    auto& em = editingTarget->GetEntityManager();

    ImGui::Begin("Hierarchy");

    if (ImGui::Button("Add Empty")) {
        int e = em.CreateEntity();
        em.AddComponent<TransformComponent>(e);
        em.SetName(e, "Empty " + std::to_string(e));

        selectedEntity = e;
        editingName = em.GetName(e);
    }

    if (ImGui::Button("Add Rect")) {
        int e = editingTarget->AddRectEntity({ 100.0f, 100.0f }, 80.0f, 80.0f, { 0.2f, 0.8f, 0.3f }, 0);
        em.SetName(e, "Rect " + std::to_string(e));

        selectedEntity = e;
        editingName = em.GetName(e);
    }

    char spritePathBuf[256]{};
    std::snprintf(spritePathBuf, sizeof(spritePathBuf), "%s", newSpritePath.c_str());

    if (ImGui::InputText("New Sprite Path", spritePathBuf, sizeof(spritePathBuf))) {
        newSpritePath = spritePathBuf;
    }

    if (ImGui::Button("Add Sprite")) {
        int e = editingTarget->AddSpriteEntity(newSpritePath, { 100.0f, 100.0f }, 0);

        if (e != -1) {
            em.SetName(e, "Sprite " + std::to_string(e));
            selectedEntity = e;
            editingName = em.GetName(e);
        }
    }

    ImGui::Separator();

    auto alive = em.GetAliveEntities();
    for (int e : alive) {
        std::string label = em.GetName(e);
        if (label.empty()) {
            label = "Entity " + std::to_string(e);
        }

        if (ImGui::Selectable(label.c_str(), selectedEntity == e)) {
            selectedEntity = e;
            editingName = em.GetName(e);

            if (em.HasComponent<RendererComponent>(e)) {
                auto& rd = em.GetComponent<RendererComponent>(e);
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
    if (!editingTarget) return;

    auto& em = editingTarget->GetEntityManager();

    ImGui::Begin("Inspector");

    if (selectedEntity == -1 || !em.IsAlive(selectedEntity)) {
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
        std::string oldName = em.GetName(selectedEntity);
        std::string newName = editingName;

        if (oldName != newName) {
            commandStack.Do(std::make_unique<RenameEntityCommand>(
                em, selectedEntity, oldName, newName
            ));
        }
    }

    // transform
    if (em.HasComponent<TransformComponent>(selectedEntity)) {
        auto& tr = em.GetComponent<TransformComponent>(selectedEntity);

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
                    em, selectedEntity, oldValue, newValue
                ));
            }
        }

        if (ImGui::Button("Remove Transform")) {
            em.RemoveComponent<TransformComponent>(selectedEntity);
            ImGui::End();
            return;
        }
    }

    // renderer
    if (em.HasComponent<RendererComponent>(selectedEntity)) {
        auto& rd = em.GetComponent<RendererComponent>(selectedEntity);

        ImGui::Separator();
        ImGui::Text("Renderer");

        ImGui::Checkbox("Visible", &rd.visible);
        ImGui::DragInt("Layer", &rd.layer, 1);

        float color[3] = { rd.color.r, rd.color.g, rd.color.b };
        if (ImGui::ColorEdit3("Color", color)) {
            rd.color.r = color[0];
            rd.color.g = color[1];
            rd.color.b = color[2];
        }

        const char* kindItems[] = { "Shape", "Sprite" };
        int kindIndex = (rd.kind == RenderKind::Shape) ? 0 : 1;

        if (ImGui::Combo("Kind", &kindIndex, kindItems, IM_ARRAYSIZE(kindItems))) {
            if (kindIndex == 0) {
                rd.kind = RenderKind::Shape;
                rd.type = ShapeType::Rect;
                rd.data.rect.width = 64.0f;
                rd.data.rect.height = 64.0f;
            }
            else {
                rd.kind = RenderKind::Sprite;
                rd.sprite.texturePath = "resources/testSprites/test1.png";
                rd.sprite.texture = GetTexture(rd.sprite.texturePath);
                editingTexturePath = rd.sprite.texturePath;
            }
        }

        if (rd.kind == RenderKind::Shape) {
            const char* shapeItems[] = { "Triangle", "Quad", "Rect" };

            int typeIndex = 0;
            if (rd.type == ShapeType::Triangle) typeIndex = 0;
            else if (rd.type == ShapeType::Quad) typeIndex = 1;
            else if (rd.type == ShapeType::Rect) typeIndex = 2;

            if (ImGui::Combo("Shape Type", &typeIndex, shapeItems, IM_ARRAYSIZE(shapeItems))) {
                if (typeIndex == 0) {
                    rd.type = ShapeType::Triangle;
                    rd.data.triangle.a = { 0.0f, 0.0f };
                    rd.data.triangle.b = { 64.0f, 0.0f };
                    rd.data.triangle.c = { 32.0f, 64.0f };
                }
                else if (typeIndex == 1) {
                    rd.type = ShapeType::Quad;
                    rd.data.quad.a = { -32.0f, -32.0f };
                    rd.data.quad.b = { 32.0f, -32.0f };
                    rd.data.quad.c = { 32.0f,  32.0f };
                    rd.data.quad.d = { -32.0f,  32.0f };
                }
                else {
                    rd.type = ShapeType::Rect;
                    rd.data.rect.width = 64.0f;
                    rd.data.rect.height = 64.0f;
                }
            }

            if (rd.type == ShapeType::Rect) {
                ImGui::DragFloat("Width", &rd.data.rect.width, 1.0f, 0.0f);
                ImGui::DragFloat("Height", &rd.data.rect.height, 1.0f, 0.0f);
            }
            else if (rd.type == ShapeType::Triangle) {
                float a[2] = { rd.data.triangle.a.x, rd.data.triangle.a.y };
                float b[2] = { rd.data.triangle.b.x, rd.data.triangle.b.y };
                float c[2] = { rd.data.triangle.c.x, rd.data.triangle.c.y };

                if (ImGui::DragFloat2("A", a, 1.0f)) rd.data.triangle.a = { a[0], a[1] };
                if (ImGui::DragFloat2("B", b, 1.0f)) rd.data.triangle.b = { b[0], b[1] };
                if (ImGui::DragFloat2("C", c, 1.0f)) rd.data.triangle.c = { c[0], c[1] };
            }
            else if (rd.type == ShapeType::Quad) {
                float a[2] = { rd.data.quad.a.x, rd.data.quad.a.y };
                float b[2] = { rd.data.quad.b.x, rd.data.quad.b.y };
                float c[2] = { rd.data.quad.c.x, rd.data.quad.c.y };
                float d[2] = { rd.data.quad.d.x, rd.data.quad.d.y };

                if (ImGui::DragFloat2("A", a, 1.0f)) rd.data.quad.a = { a[0], a[1] };
                if (ImGui::DragFloat2("B", b, 1.0f)) rd.data.quad.b = { b[0], b[1] };
                if (ImGui::DragFloat2("C", c, 1.0f)) rd.data.quad.c = { c[0], c[1] };
                if (ImGui::DragFloat2("D", d, 1.0f)) rd.data.quad.d = { d[0], d[1] };
            }
        }
        else if (rd.kind == RenderKind::Sprite) {
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
            em.RemoveComponent<RendererComponent>(selectedEntity);
            editingTexturePath.clear();
            ImGui::End();
            return;
        }
    }
    else {
        if (ImGui::Button("Add Renderer")) {
            RendererComponent rd{};
            rd.visible = true;
            rd.kind = RenderKind::Shape;
            rd.type = ShapeType::Rect;
            rd.data.rect.width = 64.0f;
            rd.data.rect.height = 64.0f;
            rd.color = { 1.0f, 1.0f, 1.0f };
            rd.layer = 0;

            commandStack.Do(
                std::make_unique<AddComponentCommand<RendererComponent>>(
                    em, selectedEntity, rd
                )
            );
        }
    }

    // collider
    if (em.HasComponent<ColliderComponent>(selectedEntity)) {
        auto& cl = em.GetComponent<ColliderComponent>(selectedEntity);

        ImGui::Separator();
        ImGui::Text("Collider");

        ImGui::DragFloat("Width", &cl.width, 1.0f, 0.0f);
        ImGui::DragFloat("Height", &cl.height, 1.0f, 0.0f);
        ImGui::Checkbox("Is Trigger", &cl.isTrigger);

        if (ImGui::Button("Remove Collider")) {
            em.RemoveComponent<ColliderComponent>(selectedEntity);
            ImGui::End();
            return;
        }
    }
    else {
        if (ImGui::Button("Add Collider")) {
            ColliderComponent cl{};
            cl.width = 32.0f;
            cl.height = 32.0f;

            commandStack.Do(
                std::make_unique<AddComponentCommand<ColliderComponent>>(
                    em, selectedEntity, cl
                )
            );
        }
    }

    ImGui::End();
}