#pragma once
#include "Component.h"
#include "Color.h"
#include "Vec2.h"

enum class ShapeType {
	Triangle,
	Quad,
	Rect

};

struct TriangleData {
	Vec2 a{};
	Vec2 b{};
	Vec2 c{};

	Color3 color{};
};


struct QuadData {
	Vec2 a{};
	Vec2 b{};
	Vec2 c{};
	Vec2 d{};


	Color3 color{};
};

struct RectData {

	float width = 1.f;
	float height = 1.f;


	Color3 color{};
};

class RendererComponent {
public:

	ShapeType type = ShapeType::Triangle;
	bool visible = true;
	int layer = 0;

	union ShapeData {
		TriangleData triangle;
		QuadData quad;
		RectData rect;

	} data;

private:

	

};
