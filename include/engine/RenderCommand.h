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
	
	std::array<float, 8> vertices;

};

struct SpriteCommand {
	Texture2D* texture;

	std::array<float, 8> positions;
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