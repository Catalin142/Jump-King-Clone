#include "map.h"

#include <fstream>

Map::Map(const std::string& filepath)
{
	load(filepath);
}

Map::~Map()
{
	for (const std::pair<const char, Texture*>& it : textures)
		delete it.second;
	
	textures.clear();
}

void Map::load(const std::string& filepath)
{
	std::ifstream map_file(filepath);
	std::string line;

	while (std::getline(map_file, line))
	{
		if (line.find(':') == std::string::npos)
			grid.push_back(line);
	
		else
		{	
			char symbol = line[0];
			std::string texture_filepath(line.begin() + 2, line.end());

			textures[symbol] = new Texture(texture_filepath);
		}

	}
}
