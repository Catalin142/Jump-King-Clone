#include "map.h"
#include "graphics/spritesheet.h"

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
		if (line.empty())
			continue;

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

			std::string texture_filepath(line.begin() + 2, line.end() - 4);
			u32 sprite_width  = line[line.size() - 3] - '0';
			u32 sprite_height = line[line.size() - 1] - '0';

			if (sprite_sheet)
				delete sprite_sheet;

			tile_size.x = (f32)sprite_width;
			tile_size.y = (f32)sprite_height;
			sprite_sheet = new Spritesheet(texture_filepath, sprite_width, sprite_height);
		}
	}

	player_position.y = f32(grid.size() - player_position.y);
}

char Map::get_at(u32 x, u32 y) const
{
	if (y < 0 || y >= grid.size())
		return 0;

	const std::string& line = grid[grid.size() - y - 1];
	if (x < 0 || x >= line.size())
		return 0;

	return line[x];
}

vec2 Map::get_position_for(u32 x, u32 y) const
{
	vec2 res;
	res.x = x * tile_size.x;
	res.y = y * tile_size.y;
	return res;
}
