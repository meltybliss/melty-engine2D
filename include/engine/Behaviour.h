#pragma once

class EntityManager;
class SceneContext;


class Behaviour {
public:
	virtual ~Behaviour() = default;
	virtual void BeginPlay() = 0;
	virtual void Tick(float dt) = 0;

	void Bind(EntityManager* em, SceneContext* ctx, int entity) {
		m_em = em;
		m_ctx = ctx;
		this->entity = entity;
	}

protected:
	EntityManager* m_em = nullptr;
	SceneContext* m_ctx = nullptr;
	int entity = -1;
};