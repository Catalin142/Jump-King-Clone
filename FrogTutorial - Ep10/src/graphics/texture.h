#pragma once
#include "core/core.h"
#include <string>

class Texture
{
public:
	Texture(const std::string& filepath);

	void bind(int slot = 0);

private:
	u32 m_handle;
	u32 m_width, m_height;
};