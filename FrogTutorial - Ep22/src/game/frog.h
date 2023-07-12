#pragma once

#include "core/core.h"
#include "graphics/texture.h"

class Map;
class Frog
{
public:
	Frog();
	~Frog();

	void update(f32 delta_time);
	void resolve_collision(const vec2& contact_normal, f32 t);
	void apply_velocity();

public:
	Texture* texture;
	vec2 position{ 0.0f, 0.0f }, collider_size{ 12.0f, 16.0f }, velocity{ 0.0f, -0.1f };

	bool grounded = false;
	bool space_state = false;

	bool accumulating = false;
	bool can_accumulate = true;

	const f32 min_jump_force = 50.0f;
	const f32 max_jump_force = 340.0f;
	f32 jump_force = min_jump_force;

	const f32 jump_accumulation_speed = 700.0f;
	const f32 walk_speed = 100.0f;
	const f32 walk_deceleration = 10.0f;

	f32 leap_direction = 0.0f;
	const f32 leap_velocity = 90.0f;

	const f32 gravity_scale = 10.0f;

};