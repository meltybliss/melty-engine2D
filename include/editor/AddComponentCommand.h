#pragma once
#include "ICommand.h"
#include "engine/EntityManager.h"

template<typename T>
class AddComponentCommand : public ICommand {
public:

	AddComponentCommand(EntityManager& em, int entity, T& initialValue) : m_em(em), m_entity(entity),
		initialValue(initialValue) {};

	void Execute() override {
		if (added) return;
		if (m_em.HasComponent<T>(entity)) return;

		m_em.AddComponent<T>(entity);
		m_em.GetComponent<T>(entity) = initialValue;

		added = true;
	}

	void Undo() override {
		if (!added) return;
		if (!m_em.HasComponent<T>(entity)) return;

		m_em.RemoveComponent<T>(entity);
		added = false;
	}

private:

	EntityManager& m_em;
	int m_entity = -1;
	bool added = false;
	T initialValue{};
};
