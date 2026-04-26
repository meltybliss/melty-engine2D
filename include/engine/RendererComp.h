#pragma once
#include "Component.h"
#include "Color.h"
#include "Texture2D.h"
#include "Vec2.h"
#include <string>

enum class ShapeType {
	Triangle,
	Quad,
	Rect,

};

enum class RenderKind {
	Shape,
	Sprite,
};

struct TriangleData {
	Vec2 a{};
	Vec2 b{};
	Vec2 c{};

};

struct SpriteData {

	Texture2D* texture = nullptr;
	std::string texturePath;
};


struct QuadData {
	Vec2 a{};
	Vec2 b{};
	Vec2 c{};
	Vec2 d{};

};

struct RectData {

	float width = 1.f;
	float height = 1.f;

};

class RendererComponent : public Component {
public:

	RenderKind kind = RenderKind::Shape;
	ShapeType type = ShapeType::Triangle;
	bool visible = true;
	int layer = 0;
	Color3 color{1.f, 1.f, 1.f};

	union ShapeData {
		TriangleData triangle;
		QuadData quad;
		RectData rect;

		ShapeData() : rect{} {}
		~ShapeData() {}

	} data;

	SpriteData sprite;

private:

	

};
