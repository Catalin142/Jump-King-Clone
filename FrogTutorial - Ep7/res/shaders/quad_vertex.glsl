#version 330 core

layout (location = 0) in vec3 vertex_pos;
layout (location = 1) in vec3 vertex_color;

out vec3 out_color;

void main()
{
   gl_Position = vec4(vertex_pos.x, vertex_pos.y, vertex_pos.z, 1.0);
   out_color = vertex_color;
}