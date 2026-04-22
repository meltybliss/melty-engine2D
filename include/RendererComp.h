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
};


struct QuadData {
	Vec2 a{};
	Vec2 b{};
	Vec2 c{};
	Vec2 d{};
};

struct RectData {

	Vec2 pos{};
	float width = 1.f;
	float height = 1.f;

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
