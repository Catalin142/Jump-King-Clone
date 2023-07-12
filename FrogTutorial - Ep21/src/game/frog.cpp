#include "frog.h"
#include "core/input.h"
#include "map.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

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
		velocity.x += 1.0f;
	if (Input::buttons[GLFW_KEY_A])
		velocity.x -= 1.0f;
	if (Input::buttons[GLFW_KEY_W])
		velocity.y += 1.0f;
	if (Input::buttons[GLFW_KEY_S])
		velocity.y -= 1.0f;

	velocity = velocity.normalize();
	velocity.x *= delta_time * 50.0f;
	velocity.y *= delta_time * 50.0f;
}

void Frog::resolve_collision(const vec2& contact_point, const vec2& contact_normal, float t)
{
	if (contact_normal.x != 0.0f)
		velocity.x = -velocity.x;
	if (contact_normal.y != 0.0f)
		velocity.y = -velocity.y;

}

void Frog::apply_velocity()
{
	position.x += velocity.x;
	position.y += velocity.y;
}
