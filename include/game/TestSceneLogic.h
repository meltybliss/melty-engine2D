#pragma once
#include "engine/SceneLogic.h"
#include "engine/AutoRegister.h"

class TestSceneLogic : public SceneLogic {
public:

	void Tick(float dt) override {
		
		auto& tr = m_em->GetComponent<TransformComponent>(entity);

		tr.position.x += 15.f * dt;
		
	}

	void BeginPlay() override {
		int e = m_em->CreateEntity();

		auto& rd = m_em->AddComponent<RendererComponent>(e);
		rd.color = { 1.0f, 1.0f, 1.0f };
		rd.kind = RenderKind::Shape;
		rd.type = ShapeType::Rect;
		rd.data.rect.height = 40.0f;
		rd.data.rect.width = 40.0f;
		rd.layer = 0;

		auto& tr = m_em->AddComponent<TransformComponent>(e);
		tr.position.y = 100.0f;

		entity = e;

	}

private:
	int entity = -1;

};


REGISTER_SCENELOGIC(TestSceneLogic, "TestScene");