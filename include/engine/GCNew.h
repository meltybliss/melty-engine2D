#pragma once

#include "GCManager.h"


#define GC_NEW_SCENE(TYPE, ...) \
	gGCM->NewSceneObject<TYPE>(__VA_ARGS__);

#define GC_NEW(TYPE, ...) \
	gGCM->NewObject<TYPE>(__VA_ARGS__);


#define GC_DESTROY(OBJ) \
	gGCM->Destroy(OBJ);