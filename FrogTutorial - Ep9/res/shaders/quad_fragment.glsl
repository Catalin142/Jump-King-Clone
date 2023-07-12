#version 330 core

layout (location = 0) out vec4 frag_color;

in vec3 out_color;

uniform float multiplier;

void main()
{
	frag_color = vec4(out_color * multiplier, 1.0f);
}