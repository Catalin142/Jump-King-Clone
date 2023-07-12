#pragma once

#include "frog.h"
#include "map.h"

class Scene
{
public:
	void update(float delta_time);

	void load_map(const std::string& map_filepath);

public:
	Map map{};
	Frog player{};
};