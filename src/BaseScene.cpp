#include "BaseScene.h"
#include "TextureAPI.h"


void BaseScene::Render() {
	renderSystem.Render(entityManager);
}

int BaseScene::CreateRectEntity(const Vec2& pos, float w, float h, const Color3& color, int layer) {

	int e = entityManager.CreateEntity();

	entityManager.AddComponent<TransformComponent>(e);
	entityManager.AddComponent<RendererComponent>(e);

	auto& rd = entityManager.GetComponent<RendererComponent>(e);
	rd.data.rect.width = w;
	rd.data.rect.height = h;
	rd.kind = RenderKind::Shape;
	rd.type = ShapeType::Rect;
	rd.color = color;
	rd.layer = layer;
	rd.visible = true;

	auto& tr = entityManager.GetComponent<TransformComponent>(e);
	tr.position = pos;
	tr.Scale = { 1.0f, 1.0f };
	tr.rotation = 0.0f;

	return e;
}


int BaseScene::CreateSpriteEntity(const std::string& texturePath, const Vec2& pos, int layer) {
	int e = entityManager.CreateEntity();

	entityManager.AddComponent<RendererComponent>(e);
	entityManager.AddComponent<TransformComponent>(e);

	auto& rd = entityManager.GetComponent<RendererComponent>(e);
	rd.kind = RenderKind::Sprite;
	rd.sprite.texture = GetTexture(texturePath);
	rd.color = {1.0f, 1.0f, 1.0f};
	rd.layer = layer;
	rd.visible = true;

	auto& tr = entityManager.GetComponent<TransformComponent>(e);
	tr.position = pos;
	tr.Scale = { 1.0f, 1.0f };
	tr.rotation = 0.0f;

	return e;
}