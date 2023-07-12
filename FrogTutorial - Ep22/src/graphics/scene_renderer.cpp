#include "scene_renderer.h"

#include "graphics/gl_objects.h"
#include "graphics/shader.h"
#include "spritesheet.h"

#include "game/scene.h"
#include "game/map.h"

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
		i32 camera_begin_x, camera_begin_y, camera_end_x, camera_end_y;

		const Camera& cam = scene->camera;

		camera_begin_x = i32(cam.position.x - cam.size.x / 2.0f) / 8 - 1;
		camera_end_x   = i32(cam.position.x + cam.size.x / 2.0f) / 8 + 1;

		camera_begin_y = i32(cam.position.y - cam.size.y / 2.0f) / 8 - 1;
		camera_end_y   = i32(cam.position.y + cam.size.y / 2.0f) / 8 + 1;

		for (i32 y = camera_begin_y; y <= camera_end_y; y++)
		{
			for (i32 x = camera_begin_x; x <= camera_end_x; x++)
			{
				char current_tile_type = map.get_at(x, y);

				if (current_tile_type == ' ' || current_tile_type == 0)
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

				m_shader.set_uniform_vec2("render_size", 320, 180);
				vec2 tile_position = map.get_position_for(x, y);
				m_shader.set_uniform_vec2("position", tile_position.x, tile_position.y);
				m_shader.set_uniform_vec2("size", (f32)8, (f32)8);
				m_shader.set_uniform_float("multiplier", 1);
				m_shader.set_uniform_int("tex", 0);

				m_vao.bind();
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			}
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

		const Camera& cam = scene->camera;
		m_shader.set_uniform_vec2("camera_size", cam.size.x, cam.size.y);
		m_shader.set_uniform_vec2("camera_position", cam.position.x, cam.position.y);
		m_shader.set_uniform_vec2("position", player.position.x, player.position.y);
		m_shader.set_uniform_vec2("size", (f32)player.texture->width, (f32)player.texture->width);
		m_shader.set_uniform_int("tex", 0);

		m_vao.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}
