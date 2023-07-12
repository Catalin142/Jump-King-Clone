#pragma once
#include "core/core.h"
#include <string>
#include <unordered_map>

class Spritesheet;
class Map
{
public:
	Map() = default;
	~Map();

	void load_level(const std::string& filepath);
	vec2 player_position{ -1.0f, -1.0f };

	char get_at(u32 x, u32 y) const;
	vec2 get_position_for(u32 x, u32 y) const;

public:
	std::vector<std::string> grid;
	Spritesheet* spritesheet = nullptr;

	vec2 tile_size;

private:
};