#include "engine/InputAPI.h"
#include "engine/Input.h"
#include "engine/Engine.h"

bool IsPressed(int key) {
	return gEngine->GetInput().IsPressed(key);
}

bool IsReleased(int key) {
	return gEngine->GetInput().IsReleased(key);
}