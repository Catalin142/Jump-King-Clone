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
#include "graphics/scene_renderer.h"

#include "game/scene.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


int main()
{
	{
		Window* window = new Window(1600, 900, "FrogTutorial");
		Input::init(window);
		SceneRenderer scene_renderer;

		f32 delta_time = 0, beg_time = 0, last_time = 0;

		Scene scene;
		scene.load_map("res/maps/level1.map");
		
		while (window->opened)
		{
			beg_time = (f32)glfwGetTime();
			delta_time = beg_time - last_time;
			last_time = beg_time;

			scene_renderer.clear(0.2f, 0.2f, 0.2f);

			scene.update(delta_time);
			scene_renderer.render_scene(&scene);

			window->pool_events();
		}

		delete window;
	}

	return 0;
}