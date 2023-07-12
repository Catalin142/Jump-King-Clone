#pragma once
#include "frog.h"
#include "map.h"

class PhysicsWorld
{
public:
	PhysicsWorld() = default;
	void step(Frog& player, const Map& map);

private:
	bool ray_vs_quad(const vec2& ray_origin, const vec2& ray_direction, const vec2& b_pos, const vec2& b_size, vec2& contact_normal, float& t);

private:
	const i32 m_player_check_size = 4;
};