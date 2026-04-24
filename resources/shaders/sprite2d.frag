#version 330 core

in vec2 vUV;

uniform sampler2D uTexture;
uniform vec4 uColor;

out vec4 FragColor;

void main() {
	vec4 texColor = texture(uTexture, vUV);

	FragColor = texColor * uColor;

}