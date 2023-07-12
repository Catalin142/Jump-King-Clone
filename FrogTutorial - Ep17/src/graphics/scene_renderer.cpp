#include "scene_renderer.h"

#include "graphics/gl_objects.h"
#include "graphics/shader.h"

#include "game/scene.h"

#include <GL/glew.h>

SceneRenderer::SceneRenderer()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float vertices[] = {
		 0.5f,  0.5f, 1.0f, 1.0f,
		 0.5f, -0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 1.0f,
	};
	m_vbo = new VertexBuffer(sizeof(vertices), vertices);

	uint32_t indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	IndexBuffer* ibo = new IndexBuffer(sizeof(indices), indices);

	m_vao.init(m_vbo, ibo);
	m_vao.set_layout(4, {
		{2, 0},
		{2, 2 * sizeof(float)}
		});

	m_shader.load("res/shaders/quad_vertex.glsl", "res/shaders/quad_fragment.glsl");
}

void SceneRenderer::clear(f32 r, f32 g, f32 b)
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void SceneRenderer::render_scene(const Scene* scene)
{
	{
		const Map& map = scene->map;

		i32 initial_position_x = 0;
		i32 initial_position_y = 0;

		for (i32 i = (i32)map.grid.size() - 1; i >= 0; i--)
		{
			const std::string& line = map.grid[i];
			initial_position_x = 0;
			for (size_t char_index = 0; char_index < line.size(); char_index++)
			{
				char current_tile_type = line[char_index];
				initial_position_x += 8;

				if (current_tile_type == ' ')
					continue;

				f32 width_coef  = 1.0f / 3.0f;
				f32 height_coef = 1.0f / 3.0f;

				u32 current_tile_index = u32(current_tile_type - '0');
				f32 x_position = f32(current_tile_index % 3);
				f32 y_position = f32(current_tile_index / 3);

				float vertices[] = {
					 0.5f,  0.5f, (x_position + 1.0f) * width_coef, (y_position + 1.0f) * height_coef,
					 0.5f, -0.5f, (x_position + 1.0f) * width_coef,  y_position * height_coef,
					-0.5f, -0.5f,  x_position * width_coef,  y_position * height_coef,
					-0.5f,  0.5f,  x_position * width_coef, (y_position + 1.0f)* height_coef,
				};
				m_vbo->set_data(sizeof(vertices), vertices);

				m_shader.bind();
				map.sprite_sheet->bind();

				m_shader.set_uniform_vec2("camera_size", 320, 180);
				m_shader.set_uniform_vec2("position", (f32)initial_position_x, (f32)initial_position_y);
				m_shader.set_uniform_vec2("size", (f32)8, (f32)8);
				m_shader.set_uniform_float("multiplier", 1);
				m_shader.set_uniform_int("tex", 0);

				m_vao.bind();
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			}
			initial_position_y += 8;
		}
	}

	{
		const Frog& player = scene->player;

		float vertices[] = {
			 0.5f,  0.5f, 1.0f, 1.0f,
			 0.5f, -0.5f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 1.0f,
		};
		m_vbo->set_data(sizeof(vertices), vertices);

		m_shader.bind();
		player.texture->bind();

		m_shader.set_uniform_vec2("camera_size", 320, 180);
		m_shader.set_uniform_vec2("position", player.position.x, player.position.y);
		m_shader.set_uniform_vec2("size", player.size.x, player.size.y);
		m_shader.set_uniform_int("tex", 0);

		m_vao.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}
