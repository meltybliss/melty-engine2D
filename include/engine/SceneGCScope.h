#pragma once
#include "GCObject.h"
#include <vector>

class SceneGCScope {
public:

	SceneGCScope();

	std::vector<GCObject*> sceneObjects;

};

extern SceneGCScope* gSceneGCScope;