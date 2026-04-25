#pragma once
#include "Engine.h"

inline Texture2D* GetTexture(const std::string& path) {
	return gEngine->GetTextureManager().GetTexture(path);
}

inline Texture2D* LoadTexture(const std::string& path) {
	return gEngine->GetTextureManager().LoadTexture(path);
}

inline void UnloadAll() {
	gEngine->GetTextureManager().UnloadAll();
}