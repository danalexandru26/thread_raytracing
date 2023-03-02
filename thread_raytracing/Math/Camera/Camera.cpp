#pragma once

#include"Camera.hpp"

namespace math
{
	camera::camera(double viewport_height, double viewport_width, double focal_length)
	{
		origin = vec3<double>(0.0f);
		vertical = vec3<double>(0.0f, viewport_height, 0.0f);
		horizontal = vec3<double>(viewport_width, 0.0f, 0.0f);

		lcorner = origin - horizontal / 2.0 - vertical / 2.0 - vec3<double>(0.0, 0.0, focal_length);
	}

	ray camera::emit(double i, double j)
	{
		return ray(origin, lcorner + i * vertical + j * horizontal - origin);
	}
}