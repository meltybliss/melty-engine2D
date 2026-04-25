#pragma once
#include "ICommand.h"
#include "engine/EntityManager.h"

template<typename T>
class AddComponentCommand : public ICommand {
public:

	AddComponentCommand(EntityManager& em, int entity, const T& initialValue = T{}) : m_em(em), m_entity(entity),
		initialValue(initialValue) {};

	void Execute() override {
		if (added) return;
		if (m_em.HasComponent<T>(m_entity)) return;

		m_em.AddComponent<T>(m_entity);
		m_em.GetComponent<T>(m_entity) = initialValue;

		added = true;
	}

	void Undo() override {
		if (!added) return;
		if (!m_em.HasComponent<T>(m_entity)) return;

		m_em.RemoveComponent<T>(m_entity);
		added = false;
	}

private:

	EntityManager& m_em;
	int m_entity = -1;
	bool added = false;
	T initialValue{};
};
