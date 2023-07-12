#pragma once
#include <cinttypes>
#include <cmath>

using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using f32 = float;
using d64 = double;

struct vec2
{
	f32 x, y;
	vec2 normalize()
	{
		vec2 res{ 0.0f, 0.0f };
		if (x == 0.0f && y == 0.0f)
			return res;

		f32 length = std::sqrt(x * x + y * y);
		res.x = x / length;
		res.y = y / length;
		return res;
	}
};

struct quad
{
	// bottom left, top left, top right, bottom right
	vec2 bl, tl, tr, br;
};