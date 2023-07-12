#pragma once

#include "core/core.h"
#include "graphics/spritesheet.h"

class Map;

struct animation
{
	u32 row, frames;
	u32 current_frame = 0;
	f32 animation_speed;
	f32 current_animation_time = 0.0f;

	void update(f32 delta_time)
	{
		current_animation_time += delta_time;
		if (current_animation_time > animation_speed)
		{
			current_frame++;
			current_animation_time = 0.0f;
		}

		current_frame %= frames;
	}
};

enum class frog_state
{
	IDLE,
	WALK,
	JUMP,
	ACCUMULATING,
};

class Frog
{
public:
	Frog();
	~Frog();

	void update(f32 delta_time);
	void resolve_collision(const vec2& contact_normal, f32 t);
	void apply_velocity();

	const animation& get_current_animation() const;

public:
	Spritesheet* spritesheet;
	vec2 position{ 0.0f, 0.0f }, collider_size{ 28.0f, 30.0f }, velocity{ 0.0f, -0.1f };

	frog_state state = frog_state::IDLE;
	animation idle_animation;
	animation walk_animation;
	animation jump_animation;
	animation accumulate_animation;

	bool grounded = false;
	bool space_state = false;

	bool accumulating = false;
	bool can_accumulate = true;

	const f32 min_jump_force = 100.0f;
	const f32 max_jump_force = 450.0f;
	f32 jump_force = min_jump_force;

	const f32 jump_accumulation_speed = 400.0f;
	const f32 walk_speed = 120.0f;
	const f32 walk_deceleration = 20.0f;

	f32 leap_direction = 0.0f;
	const f32 leap_velocity = 140.0f;

	const f32 gravity_scale = 9.8f;

private:
	void update_animations(f32 delta_time);
};