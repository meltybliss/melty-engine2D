#include "engine/Input.h"

bool Input::IsKeyPressed(KeyCode key) const {
	int index = static_cast<int>(key);

	if (index < 0 || index >= 512) return false;
	return keys[index];
}

bool Input::IsKeyReleased(KeyCode key) const {
	int index = static_cast<int>(key);

	if (index < 0 || index >= 512) return false;
	return previous[index] && !keys[index];
}

void Input::Tick(GLFWwindow* window) {

	for (int i = 0; i < 512; i++) {
		keys[i] = (glfwGetKey(window, i) == GLFW_PRESS);
	}

}