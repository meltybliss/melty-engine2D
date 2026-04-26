#pragma once
#include "SnapShot.h"
#include "BaseScene.h"


class SceneSnapshotSerializer {
public:

	static SceneSnapshot Build(const BaseScene& scene);

	static void Restore(BaseScene& scene, const SceneSnapshot& snapshot);
};