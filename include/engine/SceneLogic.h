#pragma once


class EntityManager;

class SceneLogic {
public:
	virtual ~SceneLogic() = default;
	virtual void Tick(float dt) = 0;
	virtual void BeginPlay() = 0;

	void Bind(EntityManager* em) {
		m_em = em;
	}

protected:
	EntityManager* m_em;
};
