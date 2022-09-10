#version 410 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_texture_coords;
layout(location = 3) in float a_texture_index;

uniform mat4 u_view_projection;

layout(location = 0) out vec4 v_color;
layout(location = 1) out vec2 v_texture_coords;
layout(location = 2) out float v_texture_index;

void main() {
	v_color = a_color;
	v_texture_coords = a_texture_coords;
	v_texture_index = a_texture_index;
	gl_Position = u_view_projection * vec4(a_position, 1.0f);
}
