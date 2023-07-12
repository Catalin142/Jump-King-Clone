#pragma once
#include "core/core.h"
#include "graphics/texture.h"
#include <string>
#include <unordered_map>

class Map
{
public:
	Map(const std::string& filepath);
	~Map();

public:
	std::vector<std::string> grid;
	std::unordered_map<char, Texture*> textures;

private:
	void load(const std::string& filepath);

private:
};