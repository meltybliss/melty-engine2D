#version 330 core

out vec4 FragColor;
unifrom vec4 uColor;

void main() {
	FragColor = uColor;
}