#pragma once

class EntityManager;


class Behaviour {
public:
	virtual ~Behaviour() = default;
	virtual void BeginPlay() = 0;
	virtual void Tick(float dt) = 0;

	void Bind(EntityManager* em, int entity) {
		m_em = em;
		this->entity = entity;
	}

protected:
	EntityManager* m_em = nullptr;
	int entity = -1;
};