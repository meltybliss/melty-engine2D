#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Texture2D.h"
#include <unordered_map>
#include <string>

class TextureManager {
public:

	Texture2D* LoadTexture(const std::string& path);
	Texture2D* GetTexture(const std::string& path);

	void UnloadAll();

private:

	std::unordered_map<std::string, Texture2D> textureCache;

};