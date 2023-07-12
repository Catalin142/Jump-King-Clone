#version 330 core

layout (location = 0) out vec4 frag_color;

in vec2 out_fragment;

uniform sampler2D tex;

void main()
{
	frag_color = texture(tex, out_fragment);
}