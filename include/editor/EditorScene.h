#pragma once
#include <string>
#include "engine/BaseScene.h"
#include "CommandStack.h"

class EditorScene : public BaseScene {
public:
    void Enter() override;
    void Exit() override;
    void Tick(float dt) override;
    void Render() override;

private:
    void DrawHierarchy();
    void DrawInspector();

private:
    CommandStack commandStack;
    int selectedEntity = -1;


    std::string editingTexturePath;
    int lastSelectedEntity = -1;

    std::string newSpritePath = "resources/testSprites/test1.png";

    std::string editingName;
    Vec2 oldTransformPos{};
    bool wasEditingTransform = false;

};