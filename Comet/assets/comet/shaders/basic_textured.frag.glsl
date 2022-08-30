#version 410 core

layout(location = 0) in vec4 v_color;
layout(location = 1) in vec2 v_texture_coords;

out vec4 color;

uniform sampler2D sampler;

void main() {
	color = texture(sampler, v_texture_coords) * v_color;
}
