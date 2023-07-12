#include "camera.h"

Camera::Camera(u32 size_x, u32 size_y) : size(vec2{(f32)size_x, (f32)size_y})
{ }

void Camera::restrict(const vec2& bl, const vec2& tr)
{
	if (abs(bl.x - tr.x) < size.x)
		return;

	if (abs(bl.y - tr.y) < size.y)
		return;

	if (position.x - size.x / 2.0f < bl.x)
		position.x = bl.x + size.x / 2.0f;
	if (position.x + size.x / 2.0f > tr.x)
		position.x = tr.x - size.x / 2.0f;

	if (position.y - size.y / 2.0f < bl.y)
		position.y = bl.y + size.y / 2.0f;
	if (position.y + size.y / 2.0f > tr.y)
		position.y = tr.y - size.y / 2.0f;
}
