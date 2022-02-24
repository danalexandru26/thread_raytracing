#pragma once

#include"Camera.hpp"

namespace math
{
	camera::camera(float viewport_height, float viewport_width, float focal_length)
	{
		origin = vec3<float>(0.0f);
		vertical = vec3<float>(0.0f, viewport_height, 0.0f);
		horizontal = vec3<float>(viewport_width, 0.0f, 0.0f);

		lcorner = origin - horizontal / 2.0f - vertical / 2.0f - vec3<float>(0.0f, 0.0f, focal_length);
	}

	ray camera::emit(float i, float j)
	{
		return ray(origin, lcorner + i * vertical + j * horizontal - origin);
	}
}