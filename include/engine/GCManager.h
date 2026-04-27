#pragma once
#include "GCObject.h"
#include <vector>


struct GCSlot {

	GCObject* object;
	bool marked = false;

};

class GCManager {
public:

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


	void AddRoot(GCObject* obj);


	void MarkObject(GCObject* obj);

private:

	std::vector<GCSlot> allObjects;
	std::vector<GCObject*> roots;

	GCSlot* FindSlot(GCObject* obj);

	void ClearMark();

};