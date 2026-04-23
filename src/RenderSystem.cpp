#include "Engine.h"
#include "RenderSystem.h"


void RenderSystem::Render(EntityManager& em) {
	auto& renderer = gEngine->GetRenderer2D();

	for (size_t i = 0; i < em.GetAllEntitiesCount(); i++) {
		if (em.IsAlive(i) == 0) continue;
		if (!em.HasTransform(i)) continue;
		if (!em.HasRenderer(i)) continue;

		auto& rd = em.GetRenderer(i);
		auto& tr = em.GetTransform(i);

		if (!rd.visible) continue;

		switch (rd.type) {
			case ShapeType::Triangle:{
				auto& d = rd.data.triangle;

				renderer.SubmitTriangle(tr.position + d.a,
					tr.position + d.b,
					tr.position + d.c,
					d.color,
					rd.layer);

				break;
			}

			case ShapeType::Quad: {
				auto& d = rd.data.quad;

				renderer.SubmitQuad(tr.position + d.a,
					tr.position + d.b,
					tr.position + d.c,
					tr.position + d.d,
					d.color,
					rd.layer);

				break;

			}


			case ShapeType::Rect: {
				auto& d = rd.data.rect;

				renderer.SubmitRect(tr.position.x,
					tr.position.y,
					d.width * tr.Scale.x,
					d.height * tr.Scale.y,
					d.color,
					rd.layer);

				break;
			}

		}
		
 
	}

}