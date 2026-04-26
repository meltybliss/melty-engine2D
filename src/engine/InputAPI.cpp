#include "engine/InputAPI.h"
#include "engine/Input.h"
#include "engine/Engine.h"

bool IsKeyPressed(KeyCode key) {
	return gEngine->GetInput().IsKeyPressed(key);
}

bool IsKeyReleased(KeyCode key) {
	return gEngine->GetInput().IsKeyReleased(key);
}