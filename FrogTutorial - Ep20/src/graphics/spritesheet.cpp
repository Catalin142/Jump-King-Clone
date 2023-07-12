#include "spritesheet.h"

#include "texture.h"

Spritesheet::Spritesheet(const std::string& filepath, u32 sprite_width, u32 sprite_height) : 
	texture(new Texture(filepath)), m_sprites_on_x(texture->width / sprite_width), m_sprites_on_y(texture->height / sprite_height)
{ }

Spritesheet::~Spritesheet()
{
	delete texture;
}

quad Spritesheet::get_sprite_src(u32 x, u32 y)
{
	quad src;
	
	f32 width_coef  = 1.0f / (f32)m_sprites_on_x;
	f32 height_coef = 1.0f / (f32)m_sprites_on_y;

	src.tr = vec2((x + 1.0f) * width_coef, (y + 1.0f) * height_coef);
	src.br = vec2((x + 1.0f) * width_coef, y * height_coef);
	src.bl = vec2(x * width_coef, y * height_coef);
	src.tl = vec2(x * width_coef, (y + 1.0f)* height_coef);

	return src;
}
