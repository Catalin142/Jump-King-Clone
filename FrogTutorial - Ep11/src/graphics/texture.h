#pragma once
#include "core/core.h"
#include <string>

class Texture
{
public:
	Texture(const std::string& filepath);
	~Texture();

	void bind(int slot = 0);
	void unbind();

private:
	u32 m_handle;
	i32 m_width, m_height;
};