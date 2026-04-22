#include "Input.h"

bool Input::IsPressed(int key) const {
	if (key < 0 || key >= 512) return false;
	return keys[key];
}

bool Input::IsReleased(int key) const {
	if (key < 0 || key >= 512) return false;
	return previous[key] && !keys[key];
}

void Input::Tick(GLFWwindow* window) {

	for (int i = 0; i < 512; i++) {
		keys[i] = (glfwGetKey(window, i) == GLFW_PRESS);
	}

}