#version 410 core

layout(location = 0) in vec4 v_color;
layout(location = 1) in vec2 v_texture_coords;
layout(location = 2) in float v_texture_index;

out vec4 color;

uniform sampler2D samplers[16];

void main() {
	color = texture(samplers[int(v_texture_index)], v_texture_coords) * v_color;
}
