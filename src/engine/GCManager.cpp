#include "engine/GCManager.h"


void GCManager::AddRoot(GCObject* obj) {
	if (!obj) return;

	roots.push_back(obj);
}


void GCManager::MarkObject(GCObject* obj) {
	if (!obj) return;

	GCSlot* slot = FindSlot(obj);
	if (!slot) return;
	if (obj->IsPendingKill()) return;

	slot->marked = true;

	obj->AddReferencedObjects(*this);
}


GCSlot* GCManager::FindSlot(GCObject* obj) {
	for (auto& slot : allObjects) {
		if (slot.object == obj) {
			return &slot;
		}

	}
	return nullptr;
}


void GCManager::ClearMark(){
	for (auto& slot : allObjects) {
		slot.marked = false;
	}
}