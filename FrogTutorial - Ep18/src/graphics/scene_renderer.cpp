#include "scene_renderer.h"

#include "graphics/gl_objects.h"
#include "graphics/shader.h"
#include "spritesheet.h"

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

				u32 current_tile_index = u32(current_tile_type - '0');
				quad src_quad = map.sprite_sheet->get_sprite_src(current_tile_index % 3, current_tile_index / 3);

				float vertices[] = {
					 0.5f,  0.5f, src_quad.tr.x, src_quad.tr.y,
					 0.5f, -0.5f, src_quad.br.x, src_quad.br.y,
					-0.5f, -0.5f, src_quad.bl.x, src_quad.bl.y,
					-0.5f,  0.5f, src_quad.tl.x, src_quad.tl.y,
				};
				m_vbo->set_data(sizeof(vertices), vertices);

				m_shader.bind();
				map.sprite_sheet->texture->bind();

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
