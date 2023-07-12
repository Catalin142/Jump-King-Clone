#pragma once
#include "core/core.h"

class Camera
{
public:
	Camera() = default;
	Camera(u32 size_x, u32 size_y);
	
	vec2 position{ 0.0f, 0.0f };
	vec2 size;
};