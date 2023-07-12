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

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		Texture tex("res/textures/frog.png");
		
		float vertices[] = {
			 0.5f,  0.5f, 1.0f, 1.0f,
			 0.5f, -0.5f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 1.0f,
		};
		VertexBuffer* vbo = new VertexBuffer(sizeof(vertices), vertices);

		uint32_t indices[] = {
			0, 1, 3,
			1, 2, 3
		};
		IndexBuffer* ibo = new IndexBuffer(sizeof(indices), indices);

		VertexArray vao(vbo, ibo);
		vao.set_layout(4, {
			{2, 0},
			{2, 2 * sizeof(float)}
			});

		Shader shader("res/shaders/quad_vertex.glsl", "res/shaders/quad_fragment.glsl");

		f32 multip = 1.0f;

		f32 x = 0, y = 0;
		f32 delta_time = 0, beg_time = 0, last_time = 0;

		while (window->opened)
		{
			beg_time = (f32)glfwGetTime();
			delta_time = beg_time - last_time;
			last_time = beg_time;

			glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			if (glfwGetKey(window->get_native_window(), GLFW_KEY_W) == GLFW_PRESS)
				x += 100.0f * delta_time;
			if (glfwGetKey(window->get_native_window(), GLFW_KEY_S) == GLFW_PRESS)
				x -= 100.0f * delta_time;

			shader.bind();
			tex.bind();
			
			shader.set_uniform_vec2("camera_size", 320, 180);
			shader.set_uniform_vec2("position", x, y);
			shader.set_uniform_vec2("size", (f32)tex.width, (f32)tex.height);
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