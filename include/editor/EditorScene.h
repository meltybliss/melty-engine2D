#pragma once
#include <string>
#include "engine/SceneSnapshotSerializer.h"
#include "engine/BaseScene.h"
#include "CommandStack.h"

class EditorScene : public BaseScene {
public:

    explicit EditorScene(std::unique_ptr<BaseScene> targetScene);

    void Enter() override;
    void Exit() override;
    void Tick(float dt) override;
    void Render() override;

private:
    void DrawHierarchy();
    void DrawInspector();
    void DrawToolbar();

private:
    CommandStack commandStack;
    int selectedEntity = -1;

    bool isPlaying = false;

    SceneSnapshot playBackup{};

    std::unique_ptr<BaseScene> editingTarget;
   // std::unique_ptr<BaseScene> playTarget;



    std::string editingTexturePath;
    int lastSelectedEntity = -1;

    std::string newSpritePath = "resources/testSprites/test1.png";

    std::string editingName;
    Vec2 oldTransformPos{};
    bool wasEditingTransform = false;

};