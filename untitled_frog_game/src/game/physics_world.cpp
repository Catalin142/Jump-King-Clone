#include "physics_world.h"
#include <algorithm>
#include <iostream>

struct collision
{
	vec2 obstacle_position{ 0.0f, 0.0f };
	f32 collision_time = 0.0f;
};

void PhysicsWorld::step(Frog& player, const Map& map)
{
	if (player.velocity.x == 0.0f && player.velocity.y == 0.0f)
		return;

	i32 position_grid_x, position_grid_y;
	position_grid_x = i32(player.position.x / map.tile_size.x);
	position_grid_y = i32(player.position.y / map.tile_size.y);

	std::vector<collision> collisions;
	for (i32 y = position_grid_y - m_player_check_size; y <= position_grid_y + m_player_check_size; y++)
	{
		for (i32 x = position_grid_x - m_player_check_size; x <= position_grid_x + m_player_check_size; x++)
		{
			char current_tile_type = map.get_at(x, y);
			if (current_tile_type == ' ' || current_tile_type == 0)
				continue;

			vec2 obstacle_position = map.get_position_for(x, y);
			vec2 expanded_size;
			expanded_size.x = map.tile_size.x + player.collider_size.x;
			expanded_size.y = map.tile_size.y + player.collider_size.y;

			vec2  cn{ 0.0f, 0.0f };
			f32 t;

			if (ray_vs_quad(player.position, player.velocity, obstacle_position, expanded_size, cn, t) && t >= 0.0f && t < 1.0f)
				collisions.push_back(collision(obstacle_position, t));
		}
	}

	std::sort(collisions.begin(), collisions.end(), [&](const collision& lhs, const collision& rhs) {
		return lhs.collision_time < rhs.collision_time;
		});

	for (const collision& col : collisions)
	{
		vec2 expanded_size;
		expanded_size.x = map.tile_size.x + player.collider_size.x;
		expanded_size.y = map.tile_size.y + player.collider_size.y;

		vec2 cn{ 0.0f, 0.0f };
		f32 t;

		// because the player position will update upon resolving the collision
		if (ray_vs_quad(player.position, player.velocity, col.obstacle_position, expanded_size, cn, t) && t >= 0.0f && t < 1.0f)
			player.resolve_collision(cn, col.collision_time);
	}
}

bool PhysicsWorld::ray_vs_quad(const vec2& ray_origin, const vec2& ray_direction, const vec2& b_pos, const vec2& b_size, vec2& contact_normal, float& t)
{
	contact_normal = vec2{ 0.0f, 0.0f };

	vec2 near_contact;
	near_contact.x = ((b_pos.x - b_size.x / 2.0f) - ray_origin.x) / ray_direction.x;
	near_contact.y = ((b_pos.y - b_size.y / 2.0f) - ray_origin.y) / ray_direction.y;

	vec2 far_contact;
	far_contact.x = ((b_pos.x + b_size.x / 2.0f) - ray_origin.x) / ray_direction.x;
	far_contact.y = ((b_pos.y + b_size.y / 2.0f) - ray_origin.y) / ray_direction.y;

	if (std::isnan(far_contact.y) || std::isnan(far_contact.x)) return false;
	if (std::isnan(near_contact.y) || std::isnan(near_contact.x)) return false;

	if (near_contact.x > far_contact.x) std::swap(near_contact.x, far_contact.x);
	if (near_contact.y > far_contact.y) std::swap(near_contact.y, far_contact.y);

	if (near_contact.x > far_contact.y || near_contact.y > far_contact.x)
		return false;

	t = std::max(near_contact.x, near_contact.y);

	f32 far_hit = std::min(far_contact.x, far_contact.y);

	if (far_hit < 0.0f)
		return false;

	if (near_contact.x > near_contact.y)
	{
		if (ray_direction.x < 0.0f)
			contact_normal.x = 1.0f;
		else
			contact_normal.x = -1.0f;
	}
	else if (near_contact.x < near_contact.y)
	{
		if (ray_direction.y < 0.0f)
			contact_normal.y = 1.0f;
		else
			contact_normal.y = -1.0f;
	}
	return true;
}

