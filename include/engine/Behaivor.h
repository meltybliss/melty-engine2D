#pragma once
#include "EntityManager.h"

class Behaivor {
public:
	virtual ~Behaivor() = default;
	virtual void BeginPlay() = 0;
	virtual void Tick(float dt) = 0;

	void Bind(EntityManager* em, int entity) {
		m_em = em;
		this->entity = entity;
	}

protected:
	EntityManager* m_em;
	int entity = -1;
};