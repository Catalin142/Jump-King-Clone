#version 330 core

layout (location = 0) in vec2 vertex_pos;
layout (location = 1) in vec2 fragment_pos;

out vec2 out_fragment;

uniform vec2 camera_size;
uniform vec2 camera_position;
uniform vec2 position;
uniform vec2 size;

void main()
{
	vec2 scaled_position = vec2(vertex_pos.x * size.x + position.x - camera_position.x,
                                vertex_pos.y * size.y + position.y - camera_position.y);

    vec2 position = 2.0 * scaled_position / camera_size;

	gl_Position = vec4(position, 0.0, 1.0);

	out_fragment = fragment_pos;
}