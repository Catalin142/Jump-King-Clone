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
	spritesheet = new Spritesheet("res/textures/frog.png", 32, 32);

	idle_animation.animation_speed = 0.1f;
	idle_animation.frames = 4;
	idle_animation.row = 3;

	walk_animation.animation_speed = 0.5f;
	walk_animation.frames = 1;
	walk_animation.row = 0;

	jump_animation.animation_speed = 0.5f;
	jump_animation.frames = 1;
	jump_animation.row = 1;

	accumulate_animation.animation_speed = 0.5f;
	accumulate_animation.frames = 1;
	accumulate_animation.row = 2;
}

Frog::~Frog()
{
	delete spritesheet;
}

void Frog::update(f32 delta_time)
{
	update_animations(delta_time);

	bool current_space_state = Input::buttons[GLFW_KEY_SPACE];

	if (velocity.y != 0.0f)
		grounded = false;

	if (grounded)
	{
		if (velocity.x > 0.0f)
			velocity.x -= walk_deceleration * delta_time;
		else if (velocity.x < 0.0f)
			velocity.x += walk_deceleration * delta_time;

		if (abs(velocity.x) < 1.0f)
		{
			state = frog_state::IDLE;
			velocity.x = 0.0f;
		}

		if (!accumulating)
		{
			if (Input::buttons[GLFW_KEY_D])
				velocity.x = walk_speed * delta_time, state = frog_state::WALK;

			if (Input::buttons[GLFW_KEY_A])
				velocity.x = -walk_speed * delta_time, state = frog_state::WALK;
		}

		if (can_accumulate)
		{
			if (current_space_state == space_state && current_space_state == true)
			{
				if (jump_force < max_jump_force)
					jump_force += jump_accumulation_speed * delta_time;
				accumulating = true;

				state = frog_state::ACCUMULATING;
			}
			else accumulating = false;

			if ((current_space_state != space_state && space_state == true) || jump_force >= max_jump_force)
			{
				can_accumulate = false;
				accumulating = false;
				
				state = frog_state::JUMP;

				if (Input::buttons[GLFW_KEY_D])
					leap_direction = 1.0f;

				else if (Input::buttons[GLFW_KEY_A])
					leap_direction = -1.0f;

				else leap_direction = 0.0f;

				velocity.y = jump_force * delta_time;
				velocity.x = leap_direction * leap_velocity * delta_time;

				jump_force = min_jump_force;
			}
		}
	}

	if (current_space_state == false)
		can_accumulate = true;

	velocity.y -= gravity_scale * delta_time;

	space_state = current_space_state;
}

void Frog::resolve_collision(const vec2& contact_normal, f32 t)
{
	if (contact_normal.y == 1.0f && grounded == false)
	{
		state = frog_state::IDLE;
		grounded = true;
		velocity.x = 0.0f;
	}
	
	if (contact_normal.x != 0.0f && velocity.y != 0.0f)
		velocity.x = -velocity.x;
	if (contact_normal.x != 0.0f && velocity.y == 0.0f)
		velocity.x += contact_normal.x * abs(velocity.x) * (1.0f - t);

	velocity.y += contact_normal.y * abs(velocity.y) * (1.0f - t);
}

void Frog::apply_velocity()
{
	position.x += velocity.x;
	position.y += velocity.y;
}

const animation& Frog::get_current_animation() const
{
	switch (state)
	{
	case frog_state::IDLE:
		return idle_animation;

	case frog_state::WALK:
		return walk_animation;

	case frog_state::JUMP:
		return jump_animation;

	case frog_state::ACCUMULATING:
		return accumulate_animation;

	default:
		break;
	}
}

void Frog::update_animations(f32 delta_time)
{
	switch (state)
	{
	case frog_state::IDLE:
		idle_animation.update(delta_time);

	case frog_state::WALK:
		walk_animation.update(delta_time);

	case frog_state::JUMP:
		jump_animation.update(delta_time);

	case frog_state::ACCUMULATING:
		accumulate_animation.update(delta_time);

	default:
		break;
	}
}
