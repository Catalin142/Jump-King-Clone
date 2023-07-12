#include "scene.h"

void Scene::update(float delta_time)
{
	player.update(delta_time);
	camera.position = player.position;
}

void Scene::load_map(const std::string& map_filepath)
{
	map.load_level(map_filepath);
	player.position.x = map.player_position.x * 8.0f;
	player.position.y = map.player_position.y * 8.0f;
}
