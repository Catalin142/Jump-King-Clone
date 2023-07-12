#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <cinttypes>

#include "core/window.h"

#include "graphics/shader.h"
#include "graphics/gl_objects.h"
#include "graphics/texture.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


int main()
{
	{
		Window* window = new Window(1600, 900, "FrogTutorial");
		Texture tex("res/textures/glx.jpg");
		
		float vertices[] = {
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};
		VertexBuffer* vbo = new VertexBuffer(sizeof(vertices), vertices);

		uint32_t indices[] = {
			0, 1, 3,
			1, 2, 3
		};
		IndexBuffer* ibo = new IndexBuffer(sizeof(indices), indices);

		VertexArray vao(vbo, ibo);
		vao.set_layout(5, {
			{3, 0},
			{2, 3 * sizeof(float)}
			});

		Shader shader("res/shaders/quad_vertex.glsl", "res/shaders/quad_fragment.glsl");

		f32 multip = 1.0f;

		while (window->opened)
		{
			glClearColor(0.2f, 0.8f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			if (glfwGetKey(window->get_native_window(), GLFW_KEY_W) == GLFW_PRESS)
				multip += 0.01f;
			if (glfwGetKey(window->get_native_window(), GLFW_KEY_S) == GLFW_PRESS)
				multip -= 0.01f;

			shader.bind();
			tex.bind(1);
			
			shader.set_uniform_float("multiplier", multip);
			shader.set_uniform_int("tex", 0);

			vao.bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			window->pool_events();
		}

		delete window;
	}

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();

	return 0;
}