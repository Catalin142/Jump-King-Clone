#include "physics_world.h"

void PhysicsWorld::step(Frog& player, const Map& map)
{
	if (player.velocity.x == 0.0f && player.velocity.y == 0.0f)
		return;

	i32 position_grid_x, position_grid_y;
	position_grid_x = i32(player.position.x / 8.0f);
	position_grid_y = i32(player.position.y / 8.0f);

	for (i32 y = position_grid_y - 2; y <= position_grid_y + 2; y++)
	{
		for (i32 x = position_grid_x - 2; x <= position_grid_x + 2; x++)
		{
			char current_tile_type = map.get_at(x, y);
			if (current_tile_type == ' ')
				continue;

			vec2 obstacle_position = map.get_position_for(x, y);
			vec2 expanded_size;
			expanded_size.x = 8.0f + player.size.x;
			expanded_size.y = 8.0f + player.size.y;

			vec2 cp{ 0.0f, 0.0f }, cn{ 0.0f, 0.0f };
			f32 t;

			if (ray_vs_quad(player.position, player.velocity, obstacle_position, expanded_size, cp, cn, t) && t >= 0.0f && t < 1.0f)
				player.resolve_collision(cp, cn, t);
		}
	}
}

bool PhysicsWorld::ray_vs_quad(const vec2& ray_origin, const vec2& ray_direction, const vec2& b_pos, const vec2& b_size, vec2& contact_point, vec2& contact_normal, float& t)
{
	contact_normal = vec2{ 0.0f, 0.0f };
	contact_point = vec2{ 0.0f, 0.0f };

	vec2 t_near;
	t_near.x = ((b_pos.x - b_size.x / 2.0f) - ray_origin.x) / ray_direction.x;
	t_near.y = ((b_pos.y - b_size.y / 2.0f) - ray_origin.y) / ray_direction.y;

	vec2 t_far;
	t_far.x = ((b_pos.x + b_size.x / 2.0f) - ray_origin.x) / ray_direction.x;
	t_far.y = ((b_pos.y + b_size.y / 2.0f) - ray_origin.y) / ray_direction.y;

	if (std::isnan(t_far.y) || std::isnan(t_far.x)) return false;
	if (std::isnan(t_near.y) || std::isnan(t_near.x)) return false;


	if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
	if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

	if (t_near.x > t_far.y || t_near.y > t_far.x)
		return false;

	t = std::max(t_near.x, t_near.y);

	float t_hit_far = std::min(t_far.x, t_far.y);

	if (t_hit_far < 0.0f)
		return false;

	contact_point.x = ray_origin.x + t * ray_direction.x;
	contact_point.y = ray_origin.y + t * ray_direction.y;

	if (t_near.x > t_near.y)
	{
		if (ray_direction.x < 0.0f)
			contact_normal = { 1.0f, 0.0f };
		else
			contact_normal = { -1.0f, 0.0f };
	}
	else if (t_near.x < t_near.y)
	{
		if (ray_direction.y < 0.0f)
			contact_normal = { 0.0f, 1.0f };
		else
			contact_normal = { 0.0f, -1.0f };
	}
	return true;
}
