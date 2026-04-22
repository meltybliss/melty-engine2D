#pragma once
#include "Color.h"
#include "Vec2.h"
#include <array>

enum class CommandType {
	Triangle,
	Quad,
	Rect,
};

struct TriangleCommand {

	Color3 color;
	
	std::array<float, 6> vertices;
};

struct QuadCommand {
	Color3 color;

	std::array<float, 8> vertices;
};


struct RectCommand {
	Color3 color;

	float x = 0.f, y = 0.f;
	float w = 0.f, h = 0.f;

};


struct RenderCommand {
	CommandType type;
	int layer = 0;

	union {
		TriangleCommand triangle;
		QuadCommand quad;
		RectCommand rect;
	};

};