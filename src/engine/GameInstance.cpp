#include "engine/GameInstance.h"
#include "engine/GCManager.h"


void GameInstance::Init() {

	sceneGCScope = gGCM->NewObject<SceneGCScope>(this);
	gSceneGCScope = sceneGCScope;

}


void GameInstance::ResetSceneScope() {

	sceneGCScope = gGCM->NewObject<SceneGCScope>(this);
	gSceneGCScope = sceneGCScope;
}