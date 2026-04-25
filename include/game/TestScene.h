#pragma once
#include "engine/BaseScene.h"
#include "TestSceneLogic.h"

class TestScene : public BaseScene {
public:
    void Enter() override {
       
        CreateRectEntity({ 100.f, 100.f }, 10.f, 10.f, { 1.f, 1.f, 1.f }, 0);

        SetSceneLogic(std::make_unique<TestSceneLogic>());
    }
};