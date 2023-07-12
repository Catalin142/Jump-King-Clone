#pragma once
#include "core/core.h"

#include <string>

class Texture;
class Spritesheet
{
public:
	Spritesheet(const std::string& filepath, u32 spr_width, u32 spr_height);
	~Spritesheet();

	quad get_sprite_src(u32 x, u32 y);
	
	u32 sprite_width, sprite_height;

public:
	Texture* texture;

private:
	u32 m_sprites_on_x, m_sprites_on_y;
};