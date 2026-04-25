#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"


class Input {
public:

	bool IsPressed(int key) const;
	bool IsReleased(int key) const;

	void Tick(GLFWwindow* window);

private:

	bool keys[512]{};
	bool previous[512]{};

};