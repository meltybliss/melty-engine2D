#pragma once
#include "GCObject.h"
#include "SceneGCScope.h"
#include <vector>


struct GCSlot {

	GCObject* object;
	bool marked = false;

};

class GCManager {
public:

	GCManager();

	template<typename T, typename... Args>
	T* NewObject(Args&&... args) {
		static_assert(std::is_base_of_v<GCObject, T>, "T must derive from GCObject");

		T* obj = new T(std::forward<Args>(args)...);

		GCSlot slot;
		slot.marked = false;
		slot.object = obj;

		allObjects.push_back(slot);

		return obj;

	}

	template<typename T, typename... Args>
	T* NewSceneObject(Args&&... args) {
		T* obj = NewObject<T>(args);
		if (!obj) return nullptr;
		gSceneGCScope->sceneObjects.push_back(obj);

		return obj;

	}


	void Destroy(GCObject*& obj) {//the users themselves call this
		obj = nullptr;
	}


	void AddRoot(GCObject* obj);

	void MarkObject(GCObject* obj);

	void Collect();

private:

	std::vector<GCSlot> allObjects;
	std::vector<GCObject*> roots;

	GCSlot* FindSlot(GCObject* obj);

	void Sweep();

	void ClearMark();
	void MarkRoots();
};

extern GCManager* gGCM;