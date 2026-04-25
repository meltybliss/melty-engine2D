#include "engine/Engine.h"
#include "engine/RenderSystem.h"

static Vec2 RotateVec2(const Vec2& v, float degrees) {
	float radians = degrees * 3.14159265f / 180.0f;
	float c = std::cos(radians);
	float s = std::sin(radians);
	return {
		v.x * c - v.y * s,
		v.x * s + v.y * c
	};
}

static Vec2 TransformPoint2D(const Vec2& local, const TransformComponent& tr) {
	Vec2 scaled{
		local.x * tr.Scale.x,
		local.y * tr.Scale.y
	};

	Vec2 rotated = RotateVec2(scaled, tr.rotation);
	return tr.position + rotated;
}


void RenderSystem::Render(EntityManager& em) {
	auto& renderer = gEngine->GetRenderer2D();

	for (int i = 0; i < em.GetAllEntitiesCount(); i++) {
		if (em.IsAlive(i) == 0) continue;
		if (!em.HasComponent<TransformComponent>(i)) continue;
		if (!em.HasComponent<RendererComponent>(i)) continue;

		auto& rd = em.GetComponent<RendererComponent>(i);
		auto& tr = em.GetComponent<TransformComponent>(i);

		if (!rd.visible) continue;

		if (rd.kind == RenderKind::Shape) {

			switch (rd.type) {
				case ShapeType::Triangle: {
					auto& d = rd.data.triangle;

					renderer.SubmitTriangle(
						TransformPoint2D(d.a, tr),
						TransformPoint2D(d.b, tr),
						TransformPoint2D(d.c, tr),
						rd.color,
						rd.layer
					);

					break;
				}

				case ShapeType::Quad: {
					auto& d = rd.data.quad;

					renderer.SubmitQuad(
						TransformPoint2D(d.a, tr),
						TransformPoint2D(d.b, tr),
						TransformPoint2D(d.c, tr),
						TransformPoint2D(d.d, tr),
						rd.color,
						rd.layer
					);

					break;

				}


				case ShapeType::Rect: {
					auto& d = rd.data.rect;
					float w = d.width;
					float h = d.height;

					//the center is the reference point
					Vec2 p1 = { -w * 0.5f, -h * 0.5f };
					Vec2 p2 = { w * 0.5f, -h * 0.5f };
					Vec2 p3 = { w * 0.5f, h * 0.5f };
					Vec2 p4 = { -w * 0.5f, h * 0.5f };

					renderer.SubmitRect(
						TransformPoint2D(p1, tr),
						TransformPoint2D(p2, tr),
						TransformPoint2D(p3, tr),
						TransformPoint2D(p4, tr),
						rd.color,
						rd.layer);

					break;
				}

			}

		}
		else if (rd.kind == RenderKind::Sprite) {
			auto& d = rd.sprite;

			if (!d.texture) return;

			float w = d.texture->width;
			float h = d.texture->height;

			Vec2 p1 = { -w * 0.5f, -h * 0.5f };
			Vec2 p2 = { w * 0.5f, -h * 0.5f };
			Vec2 p3 = { w * 0.5f, h * 0.5f };
			Vec2 p4 = { -w * 0.5f, h * 0.5f};

			renderer.SubmitSprite(d.texture,
				TransformPoint2D(p1, tr),
				TransformPoint2D(p2, tr),
				TransformPoint2D(p3, tr),
				TransformPoint2D(p4, tr),
				rd.color,
				rd.layer);

			break;
		}
	}

}