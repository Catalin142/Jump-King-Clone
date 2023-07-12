#include "map.h"
#include "graphics/spritesheet.h"

#include <fstream>
#include <cassert>

Map::~Map()
{
	if (spritesheet)
		delete spritesheet;
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
			if (line.find("w:") != std::string::npos)
			{
				std::string width(line.begin() + 2, line.end());
				tile_size.x = (f32)std::stoi(width);
			}

			else if (line.find("h:") != std::string::npos)
			{
				std::string height(line.begin() + 2, line.end());
				tile_size.y = (f32)std::stoi(height);
			}

			else if (line.find("s:") != std::string::npos)
			{
				char symbol = line[0];

				std::string texture_filepath(line.begin() + 2, line.end());

				if (tile_size.x == 0.0f || tile_size.y == 0.0f)
					assert(false);

				spritesheet = new Spritesheet(texture_filepath, (u32)tile_size.x, u32(tile_size.y));
			}
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
