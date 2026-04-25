#pragma once
#include "Color.h"
#include "Vec2.h"
#include "Texture2D.h"
#include <array>

enum class CommandType {
	Triangle,
	Quad,
	Rect,
	Sprite,
};

struct TriangleCommand {

	std::array<float, 6> vertices;
};

struct QuadCommand {
	
	std::array<float, 8> vertices;
};


struct RectCommand {
	
	float x = 0.f, y = 0.f;
	float w = 0.f, h = 0.f;

};

struct SpriteCommand {
	Texture2D* texture;

	float x = 0.f;
	float y = 0.f;
};


struct RenderCommand {
	CommandType type;
	bool useShape = true;
	int layer = 0;
	Color3 color;


	union {
		TriangleCommand triangle;
		QuadCommand quad;
		RectCommand rect;
		SpriteCommand sprite;
	};

};