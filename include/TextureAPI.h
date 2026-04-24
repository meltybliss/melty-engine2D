#pragma once
#include "Engine.h"

Texture2D* GetTexture(const std::string& path) {
	return gEngine->GetTextureManager().GetTexture(path);
}

Texture2D* LoadTexture(const std::string& path) {
	return gEngine->GetTextureManager().LoadTexture(path);
}

void UnloadAll() {
	gEngine->GetTextureManager().UnloadAll();
}