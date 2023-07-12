#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <cinttypes>

#include "core/window.h"
#include "core/input.h"

#include "graphics/shader.h"
#include "graphics/gl_objects.h"
#include "graphics/texture.h"

#include "game/map.h"
#include "game/frog.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


int main()
{
	{
		Window* window = new Window(1600, 900, "FrogTutorial");
		Input::init(window);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

		f32 delta_time = 0, beg_time = 0, last_time = 0;

		Map level1("res/maps/level1.map");
		Frog player{};

		while (window->opened)
		{
			beg_time = (f32)glfwGetTime();
			delta_time = beg_time - last_time;
			last_time = beg_time;

			glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			player.update(delta_time);

			// rendering the map
			{
				i32 initial_position_x = -160;
				i32 initial_position_y = -90;

				for (i32 i = (i32)level1.grid.size() - 1; i >= 0; i--)
				{
					const std::string& line = level1.grid[i];
					initial_position_x = -160;
					for (size_t char_index = 0; char_index < line.size(); char_index++)
					{
						char current_tile_type = line[char_index];
						initial_position_x += 8;

						if (current_tile_type == ' ')
							continue;

						shader.bind();
						level1.textures[current_tile_type]->bind();

						shader.set_uniform_vec2("camera_size", 320, 180);
						shader.set_uniform_vec2("position", (f32)initial_position_x, (f32)initial_position_y);
						shader.set_uniform_vec2("size", (f32)8, (f32)8);
						shader.set_uniform_float("multiplier", 1);
						shader.set_uniform_int("tex", 0);

						vao.bind();
						glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
					}
					initial_position_y += 8;
				}
			}


			// rendering the frog
			{
				shader.bind();
				player.texture->bind();

				shader.set_uniform_vec2("camera_size", 320, 180);
				shader.set_uniform_vec2("position", player.position.x, player.position.y);
				shader.set_uniform_vec2("size", player.size.x, player.size.y);
				shader.set_uniform_float("multiplier", multip);
				shader.set_uniform_int("tex", 0);

				vao.bind();
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			}
			window->pool_events();
		}

		delete window;
	}

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();

	return 0;
}