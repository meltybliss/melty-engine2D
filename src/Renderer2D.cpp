#include "Renderer2D.h"

std::string Renderer2D::ReadFile(const std::string& path) {//static
	std::ifstream file(path);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file: " + path);
	}

	std::stringstream ss;
	ss << file.rdbuf();

	return ss.str();

}


Renderer2D::Renderer2D() {



}