#pragma once

#include "graphics/gl_objects.h"
#include "graphics/shader.h"

class Scene;

class SceneRenderer
{
public:
	SceneRenderer();

	void clear(f32 r, f32 g, f32 b);
	void render_scene(const Scene* scene);

private:
	VertexArray m_vao;
	VertexBuffer* m_vbo;
	Shader m_shader;
};