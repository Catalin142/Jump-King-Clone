#pragma once

#include "core/core.h"
#include "graphics/texture.h"

class Frog
{
public:
	Frog();
	~Frog();

	void update(f32 delta_time);

public:
	Texture* texture;
	vec2 position{ 0.0f, 0.0f }, size{ 16.0f, 16.0f };

private:

};