#pragma once


class EntityManager;
class SceneContext;

class SceneLogic {
public:
	virtual ~SceneLogic() = default;
	virtual void Tick(float dt) = 0;
	virtual void BeginPlay() = 0;

	void Bind(EntityManager* em, SceneContext* ctx) {
		m_em = em;
		m_ctx = ctx;
	}

protected:
	EntityManager* m_em;
	SceneContext* m_ctx;
};
