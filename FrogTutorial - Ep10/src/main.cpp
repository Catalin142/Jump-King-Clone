#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <cinttypes>

#include "core/window.h"

#include "graphics/shader.h"
#include "graphics/gl_objects.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "std_image.h"

int main()
{
	{
		Window* window = new Window(1600, 900, "FrogTutorial");

		u32 texture_handle;
		i32 width, height, bbp;
		stbi_set_flip_vertically_on_load(true);

		stbi_uc* tex_data = nullptr;
		tex_data = stbi_load("res/textures/glx.jpg", &width, &height, &bbp, 0);
		if (tex_data == nullptr)
			std::cerr << "Image doesn't exist\n";

		u32 internal_format = 0, format = 0;
		switch (bbp)
		{
		case 3:
			internal_format = GL_RGB8;
			format = GL_RGB;
			break;

		case 4:
			internal_format = GL_RGBA8;
			format = GL_RGBA;
			break;
		}

		glGenTextures(1, &texture_handle);
		glBindTexture(GL_TEXTURE_2D, texture_handle);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, tex_data);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(tex_data);

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
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture_handle);
			
			shader.set_uniform_float("multiplier", multip);
			shader.set_uniform_int("tex", 0);

			vao.bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			window->pool_events();
		}

		glDeleteTextures(1, &texture_handle);
		delete window;
	}

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();

	return 0;
}