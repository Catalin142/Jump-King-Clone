#include "map.h"

#include <fstream>

Map::~Map()
{
	if (sprite_sheet)
		delete sprite_sheet;
}

void Map::load_level(const std::string& filepath)
{
	std::ifstream map_file(filepath);
	std::string line;

	i32 line_index = 0;
	while (std::getline(map_file, line))
	{
		if (line.find(':') == std::string::npos)
		{
			line_index++;
			size_t player_p = line.find('p');
			if (player_p != std::string::npos)
			{
				line[player_p] = ' ';
				player_position.x = (f32)player_p;
				player_position.y = (f32)line_index;
			}

			grid.push_back(line);
		}
		else
		{	
			char symbol = line[0];
			std::string texture_filepath(line.begin() + 2, line.end());

			if (sprite_sheet)
				delete sprite_sheet;

			sprite_sheet = new Texture(texture_filepath);
		}
	}

	player_position.y = f32(grid.size() - player_position.y);
}
