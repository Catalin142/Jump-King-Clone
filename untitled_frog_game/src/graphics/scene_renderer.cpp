#include "scene_renderer.h"

#include "graphics/gl_objects.h"
#include "graphics/shader.h"
#include "spritesheet.h"
#include "texture.h"

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

		camera_begin_x = i32(cam.position.x - cam.size.x / 2.0f) / (i32)map.tile_size.x - 1;
		camera_end_x   = i32(cam.position.x + cam.size.x / 2.0f) / (i32)map.tile_size.y + 1;

		camera_begin_y = i32(cam.position.y - cam.size.y / 2.0f) / (i32)map.tile_size.x - 1;
		camera_end_y   = i32(cam.position.y + cam.size.y / 2.0f) / (i32)map.tile_size.y + 1;

		for (i32 y = camera_begin_y; y <= camera_end_y; y++)
		{
			for (i32 x = camera_begin_x; x <= camera_end_x; x++)
			{
				char current_tile_type = map.get_at(x, y);

				if (current_tile_type == ' ' || current_tile_type == 0)
					continue;

				u32 current_tile_index = u32(current_tile_type - '0');
				quad src_quad = map.spritesheet->get_sprite_src(current_tile_index % 3, current_tile_index / 3);

				float vertices[] = {
					 0.5f,  0.5f, src_quad.tr.x, src_quad.tr.y,
					 0.5f, -0.5f, src_quad.br.x, src_quad.br.y,
					-0.5f, -0.5f, src_quad.bl.x, src_quad.bl.y,
					-0.5f,  0.5f, src_quad.tl.x, src_quad.tl.y,
				};
				m_vbo->set_data(sizeof(vertices), vertices);

				m_shader.bind();
				map.spritesheet->texture->bind();

				m_shader.set_uniform_vec2("camera_size", cam.size.x, cam.size.y);
				m_shader.set_uniform_vec2("camera_position", cam.position.x, cam.position.y);
				vec2 tile_position = map.get_position_for(x, y);
				m_shader.set_uniform_vec2("position", tile_position.x, tile_position.y);
				m_shader.set_uniform_vec2("size", map.tile_size.x, map.tile_size.x);
				m_shader.set_uniform_int("tex", 0);

				m_vao.bind();
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			}
		}
	}

	{
		const Frog& player = scene->player;

		const animation& current_animation = player.get_current_animation();
		quad src_quad = player.spritesheet->get_sprite_src(current_animation.current_frame, current_animation.row);

		float vertices[] = {
			 0.5f,  0.5f, src_quad.tr.x, src_quad.tr.y,
			 0.5f, -0.5f, src_quad.br.x, src_quad.br.y,
			-0.5f, -0.5f, src_quad.bl.x, src_quad.bl.y,
			-0.5f,  0.5f, src_quad.tl.x, src_quad.tl.y,
		};
		m_vbo->set_data(sizeof(vertices), vertices);

		m_shader.bind();
		player.spritesheet->texture->bind();

		const Camera& cam = scene->camera;

		m_shader.set_uniform_vec2("camera_size", cam.size.x, cam.size.y);
		m_shader.set_uniform_vec2("camera_position", cam.position.x, cam.position.y);
		m_shader.set_uniform_vec2("position", player.position.x, player.position.y);
		m_shader.set_uniform_vec2("size", (f32)player.spritesheet->sprite_width, (f32)player.spritesheet->sprite_height);
		m_shader.set_uniform_int("tex", 0);

		m_vao.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}
