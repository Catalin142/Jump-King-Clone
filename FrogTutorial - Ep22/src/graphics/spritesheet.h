#pragma once
#include "core/core.h"

#include <string>

class Texture;
class Spritesheet
{
public:
	Spritesheet(const std::string& filepath, u32 sprite_width, u32 sprite_height);
	~Spritesheet();

	quad get_sprite_src(u32 x, u32 y);
	
public:
	Texture* texture;

private:
	u32 m_sprites_on_x, m_sprites_on_y;
};