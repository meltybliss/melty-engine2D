#include "engine/Engine.h"
#include "engine/RenderSystem.h"


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

					renderer.SubmitTriangle(tr.position + d.a,
						tr.position + d.b,
						tr.position + d.c,
						rd.color,
						rd.layer);

					break;
				}

				case ShapeType::Quad: {
					auto& d = rd.data.quad;

					renderer.SubmitQuad(tr.position + d.a,
						tr.position + d.b,
						tr.position + d.c,
						tr.position + d.d,
						rd.color,
						rd.layer);

					break;

				}


				case ShapeType::Rect: {
					auto& d = rd.data.rect;

					renderer.SubmitRect(tr.position.x,
						tr.position.y,
						d.width * tr.Scale.x,
						d.height * tr.Scale.y,
						rd.color,
						rd.layer);

					break;
				}

			}

		}
		else if (rd.kind == RenderKind::Sprite) {
			auto& d = rd.sprite;

			renderer.SubmitSprite(d.texture,
				tr.position.x,
				tr.position.y,
				rd.color,
				rd.layer);

			break;
		}
	}

}