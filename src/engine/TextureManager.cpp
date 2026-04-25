#include "engine/TextureManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

Texture2D* TextureManager::LoadTexture(const std::string& path) {
	auto it = textureCache.find(path);
	if (it != textureCache.end()) {
		return &it->second;
	}

	int width = 0;
	int height = 0;
	int channels = 0;

	stbi_set_flip_vertically_on_load(1);
	unsigned char* pixels = stbi_load(path.c_str(), &width, &height, &channels, 4);
	if (!pixels) {
		return nullptr;
	}


	GLuint texId = 0;
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA8,
		width,
		height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		pixels
	);

	stbi_image_free(pixels);

	Texture2D tex;
	tex.id = texId;
	tex.width = (float)width;
	tex.height = (float)height;

	textureCache[path] = tex;

	return &textureCache[path];
}


Texture2D* TextureManager::GetTexture(const std::string& path) {
	auto it = textureCache.find(path);
	if (it != textureCache.end()) {
		return &it->second;
	}
	else {
		return this->LoadTexture(path);
	}
}


void TextureManager::UnloadAll() {
	for (auto& pair : textureCache) {
		glDeleteTextures(1, &pair.second.id);
	}

	textureCache.clear();
}