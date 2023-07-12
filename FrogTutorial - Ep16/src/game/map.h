#pragma once
#include "core/core.h"
#include "graphics/texture.h"
#include <string>
#include <unordered_map>

class Map
{
public:
	Map() = default;
	~Map();

	void load_level(const std::string& filepath);
	vec2 player_position{ -1.0f, -1.0f };

public:
	std::vector<std::string> grid;
	std::unordered_map<char, Texture*> textures;

private:
};