#pragma once

#include"../Ray/Ray.hpp"
#include"../Vector/Vector.hpp"

namespace math
{
	class camera
	{
	public:
		camera(float viewport_height, float viewport_width, float focal_length);

		ray emit(float u, float v);

	private:
		vec3<float> horizontal;
		vec3<float> vertical;
		vec3<float> lcorner;
		vec3<float> origin;
	};
}