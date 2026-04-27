#pragma once
#include "GCObject.h"
#include "SceneGCScope.h"
#include "GCNew.h"
#include "GCMacros.h"


class GameInstance : public GCObject {
public:

	void Init();

	void SetCurrentSceneGCScope(SceneGCScope* newScope) {
		sceneGCScope = newScope;
	}

	void DestroyObject(GCObject*& object) override {
		if (object == sceneGCScope) {
			sceneGCScope = nullptr;
			object = nullptr;
		}
	}

	void ResetSceneScope();


	GC_REFERENCES_BEGIN()
		GC_REFERENCES_ADD(sceneGCScope)
	GC_REFERENCES_END()


private:
	SceneGCScope* sceneGCScope;
};
