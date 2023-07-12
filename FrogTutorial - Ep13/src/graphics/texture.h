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

public:
	i32 width, height;

private:
	u32 m_handle;
};