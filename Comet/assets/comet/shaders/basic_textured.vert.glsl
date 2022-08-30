#version 410 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_texture_coords;

layout(location = 0) out vec4 v_color;
layout(location = 1) out vec2 v_texture_coords;

void main() {
	v_color = a_color;
	v_texture_coords = a_texture_coords;
	gl_Position = vec4(a_position, 1.0f);
}
