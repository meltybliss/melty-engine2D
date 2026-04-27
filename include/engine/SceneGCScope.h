#pragma once
#include "GCObject.h"
#include "GCMacros.h"
#include <vector>
#include <algorithm>

class SceneGCScope : public GCObject {
public:

	SceneGCScope();

	void DestroyObject(GCObject*& object) override {
		if (!object) return;
		sceneObjects.erase(
			std::remove(sceneObjects.begin(), sceneObjects.end(), object),
			sceneObjects.end()
		);

		object = nullptr;
	}

	std::vector<GCObject*> sceneObjects;

	GC_REFERENCES_BEGIN()
		for (GCObject* obj : sceneObjects) {
			GC_REFERENCES_ADD(obj)
		}
	GC_REFERENCES_END()
	

};

extern SceneGCScope* gSceneGCScope;