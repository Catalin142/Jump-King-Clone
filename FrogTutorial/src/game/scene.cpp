#include "scene.h"

void Scene::update(float delta_time)
{
	player.update(delta_time);
	physics_world.step(player, map);
	player.apply_velocity();
	
	camera.position = player.position;

	f32 current_screen = (f32)(i32)(player.position.y / camera.size.y);
	f32 lower_y_limit = current_screen * camera.size.y;
	f32 upper_y_limit = (current_screen + 1.0f) * camera.size.y;

	vec2 bl{ 0.0f - map.tile_size.x / 2.0f, lower_y_limit - map.tile_size.y / 2.0f };
	vec2 tr{ camera.size.x - map.tile_size.x / 2.0f, upper_y_limit - map.tile_size.x / 2.0f };
	camera.restrict(bl, tr);
}

void Scene::load_map(const std::string& map_filepath)
{
	map.load_level(map_filepath);
	player.position.x = map.player_position.x * map.tile_size.x;
	player.position.y = map.player_position.y * map.tile_size.x;
}
