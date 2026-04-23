#include "InputAPI.h"
#include "Input.h"
#include "Engine.h"

bool IsPressed(int key) {
	return gEngine->GetInput().IsPressed(key);
}

bool IsReleased(int key) {
	return gEngine->GetInput().IsReleased(key);
}