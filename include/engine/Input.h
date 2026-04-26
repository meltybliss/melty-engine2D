#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "KeyCode.h"


class Input {
public:

	bool IsKeyPressed(KeyCode key) const;
	bool IsKeyReleased(KeyCode key) const;

	void Tick(GLFWwindow* window);

private:

	bool keys[512]{};
	bool previous[512]{};

};