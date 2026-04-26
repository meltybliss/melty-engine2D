#pragma once
#include "engine/SceneLogic.h"
#include "engine/AutoRegister.h"
#include "engine/InputAPI.h"
#include <cmath>

class TestSceneLogic : public SceneLogic {
public:
	void BeginPlay() override {
		player = m_ctx->CreateRectEntityWithCollider(
			{ 100.0f, 300.0f },
			50.0f,
			50.0f,
			{ 0.2f, 0.8f, 1.0f },
			0,
			false, // trigger?
			false  // static?
		);

		wall = m_ctx->CreateRectEntityWithCollider(
			{ 600.0f, 400.0f },
			80.0f,
			220.0f,
			{ 0.4f, 0.4f, 0.4f },
			0,
			false, // trigger?
			true   // static?
		);

		enemy = m_ctx->CreateRectEntityWithCollider(
			{ 900.0f, 300.0f },
			70.0f,
			70.0f,
			{ 1.0f, 0.2f, 0.2f },
			0,
			true,  // trigger?
			false  // static?
		);
	}

	void Tick(float dt) override {
		time += dt;

		UpdatePlayer(dt);
		UpdateEnemy(dt);
		UpdateBullet(dt);
		CheckBulletEnemyHit();
	}

private:
	int player = -1;
	int wall = -1;
	int enemy = -1;
	int bullet = -1;

	bool bulletActive = false;

	float time = 0.0f;
	float playerSpeed = 320.0f;
	float bulletSpeed = 700.0f;

	void UpdatePlayer(float dt) {
		if (!HasTransform(player)) return;

		auto& tr = m_em->GetComponent<TransformComponent>(player);

		Vec2 move{ 0.0f, 0.0f };

		if (IsKeyPressed(KeyCode::A)) move.x -= 1.0f;
		if (IsKeyPressed(KeyCode::D)) move.x += 1.0f;
		if (IsKeyPressed(KeyCode::S)) move.y += 1.0f;
		if (IsKeyPressed(KeyCode::W)) move.y -= 1.0f;

		tr.position.x += move.x * playerSpeed * dt;
		tr.position.y += move.y * playerSpeed * dt;

		if (IsKeyPressed(KeyCode::Space)) {
			FireBullet(tr.position);
		}
	}

	void UpdateEnemy(float dt) {
		if (!HasTransform(enemy)) return;

		auto& tr = m_em->GetComponent<TransformComponent>(enemy);

		tr.position.y = 300.0f + std::sin(time * 3.0f) * 150.0f;
	}

	void FireBullet(const Vec2& playerPos) {
		if (bulletActive) return;

		bullet = m_ctx->CreateRectEntityWithCollider(
			{ playerPos.x + 60.0f, playerPos.y },
			24.0f,
			8.0f,
			{ 1.0f, 1.0f, 0.2f },
			0,
			true,  // trigger
			false  // static
		);

		bulletActive = true;
	}

	void UpdateBullet(float dt) {
		if (!bulletActive) return;
		if (!HasTransform(bullet)) return;

		auto& tr = m_em->GetComponent<TransformComponent>(bullet);

		tr.position.x += bulletSpeed * dt;

		if (tr.position.x > 1280.0f) {
			m_em->DestroyEntity(bullet);
			bullet = -1;
			bulletActive = false;
		}
	}

	void CheckBulletEnemyHit() {
		if (!bulletActive) return;
		if (!m_em->IsAlive(bullet)) return;
		if (!m_em->IsAlive(enemy)) return;

		if (!m_ctx->Collisions().IsOverlapping(m_ctx->Entities(), bullet, enemy)) {
			return;
		}

		if (m_em->HasComponent<RendererComponent>(enemy)) {
			auto& rd = m_em->GetComponent<RendererComponent>(enemy);
			rd.color = { Random01(), Random01(), Random01() };
		}

		m_em->DestroyEntity(bullet);
		bullet = -1;
		bulletActive = false;
	}

	bool HasTransform(int e) const {
		return e != -1 &&
			m_em->IsAlive(e) &&
			m_em->HasComponent<TransformComponent>(e);
	}

	float Random01() const {
		static unsigned int seed = 123456789u;
		seed = seed * 1664525u + 1013904223u;
		return static_cast<float>((seed >> 8) & 0xFFFFFF) / 16777215.0f;
	}
};

REGISTER_SCENELOGIC(TestSceneLogic, "TestScene");