#include "engine/SceneSnapshotSerializer.h"
#include "engine/EntityManager.h"
#include "engine/AutoRegister.h"


SceneSnapshot SceneSnapshotSerializer::Build(const BaseScene& scene) {
	SceneSnapshot sceneSnap;

	const auto& em = scene.GetEntityManager();
	int count = em.GetAllEntitiesCount();
	for (int i = 0; i < count; i++) {
		EntitySnapshot entitySnap{};

		entitySnap.id = i;
		entitySnap.alive = em.IsAlive(i);

		entitySnap.name = em.GetName(i);
		entitySnap.tag = em.GetTag(i);

		if (em.HasComponent<RendererComponent>(i)) {
			entitySnap.hasRenderer = true;

			entitySnap.rendererCmp = em.GetComponent<RendererComponent>(i);

		}
		if (em.HasComponent<TransformComponent>(i)) {
			entitySnap.hasTransform = true;

			entitySnap.transformCmp = em.GetComponent<TransformComponent>(i);
		}
		if (em.HasComponent<ColliderComponent>(i)) {
			entitySnap.hasCollider = true;

			entitySnap.colliderCmp = em.GetComponent<ColliderComponent>(i);
		}
		if (em.HasComponent<ScriptComponent>(i)) {
			entitySnap.hasScript = true;

			auto& sc = em.GetComponent<ScriptComponent>(i);
			auto name = BehaviourRegistry::Get().GetName(sc.behaviour.get());
			if (name) {
				entitySnap.behaviourName = *name;
			}
		}

		sceneSnap.entities.push_back(entitySnap);

	}


	auto name = SceneLogicRegister::Get().GetName(scene.GetSceneLogic());
	if (name) {
		sceneSnap.sceneLogicName = *name;
	}
	
	return sceneSnap;
}


void SceneSnapshotSerializer::Restore(BaseScene& scene, const SceneSnapshot& snapshot) {
	auto& em = scene.GetEntityManager();

	em.Reset();
	auto sl = SceneLogicRegister::Get().Create(snapshot.sceneLogicName);
	if (sl) {
		scene.SetSceneLogic(std::move(sl));
	}
	for (const auto& entitySnap : snapshot.entities) {
		int e = em.CreateEntity();

		if (!entitySnap.alive) {
			em.DestroyEntity(e);
			continue;
		}

		em.SetName(e, entitySnap.name);
		em.SetTag(e, entitySnap.tag);

		if (entitySnap.hasTransform) {
			auto& tr = em.AddComponent<TransformComponent>(e);
			tr = entitySnap.transformCmp;
		}

		if (entitySnap.hasRenderer) {
			auto& rd = em.AddComponent<RendererComponent>(e);
			rd = entitySnap.rendererCmp;
		}

		if (entitySnap.hasCollider) {
			auto& cl = em.AddComponent<ColliderComponent>(e);
			cl = entitySnap.colliderCmp;
		}

		if (entitySnap.hasScript) {
			auto& sc = em.AddComponent<ScriptComponent>(e);

			auto b = BehaviourRegistry::Get().Create(entitySnap.behaviourName);
			if (b) {
				sc.behaviour = std::move(b);
			}
			
			sc.started = false;

		}

	}
}