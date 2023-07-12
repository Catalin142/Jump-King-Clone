#version 330 core

layout (location = 0) in vec2 vertex_pos;
layout (location = 1) in vec2 fragment_pos;

out vec2 out_fragment;

uniform vec2 camera_size;
uniform vec2 position;
uniform vec2 size;

void main()
{
   gl_Position = vec4(2.0 * (vertex_pos.x * size.x + position.x) / camera_size.x, 2.0 * (vertex_pos.y * size.y + position.y) / camera_size.y, 0.0, 1.0);
   out_fragment = fragment_pos;
}