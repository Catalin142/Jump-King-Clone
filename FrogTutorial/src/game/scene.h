#pragma once

#include "frog.h"
#include "map.h"
#include "camera.h"
#include "physics_world.h"

class Scene
{
public:
	void update(float delta_time);
	void load_map(const std::string& map_filepath);

public:
	Map map{};
	Frog player{};
	Camera camera{ 480, 270 };

	PhysicsWorld physics_world;
};