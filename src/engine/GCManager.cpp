#include "engine/GCManager.h"

GCManager* gGCM = nullptr;

GCManager::GCManager() {
	gGCM = this;
}

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


void GCManager::Sweep() {

	auto it = allObjects.begin();
	while (it != allObjects.end()) {
		auto& obj = it->object;
		bool marked = it->marked;

		if (!obj) {
			it = allObjects.erase(it);
			continue;
		}

		if (!marked) {
			delete obj;
			it = allObjects.erase(it);
		}
		else {
			it++;
		}
		
		
	}

}


void GCManager::MarkRoots() {
	for (auto& root : roots) {
		if (!root) continue;
		MarkObject(root);
	}

}

void GCManager::Collect() {
	ClearMark();
	MarkRoots();

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