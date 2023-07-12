#include "frog.h"
#include "core/input.h"

#include "GLFW/glfw3.h"

Frog::Frog()
{
	texture = new Texture("res/textures/frog.png");
}

Frog::~Frog()
{
	delete texture;
}

void Frog::update(f32 delta_time)
{
	if (Input::buttons[GLFW_KEY_D])
		position.x += 100.0f * delta_time;
	if (Input::buttons[GLFW_KEY_A])
		position.x -= 100.0f * delta_time;
	if (Input::buttons[GLFW_KEY_W])
		position.y += 100.0f * delta_time;
	if (Input::buttons[GLFW_KEY_S])
		position.y -= 100.0f * delta_time;
}
