#include "engine/Engine.h"
#include "editor/EditorScene.h"

#include "game/TestScene.h"

int main() {
	
	Engine engine(1280, 720);//init openGL
	engine.GetSceneManager().ChangeCurrentScene(
		std::make_unique<EditorScene>(
			std::make_unique<TestScene>()
		)
	);
	engine.Run();
}