#pragma once

#include <string>

class Texture2D;

Texture2D* GetTexture(const std::string& path);
Texture2D* LoadTexture(const std::string& path);
void UnloadAll();