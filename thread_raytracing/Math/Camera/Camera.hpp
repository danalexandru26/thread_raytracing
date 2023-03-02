#pragma once

#include"../Ray/Ray.hpp"
#include"../Vector/Vector.hpp"

namespace math
{
	class camera
	{
	public:
		camera(double viewport_height, double viewport_width, double focal_length);

		ray emit(double u, double v);
	private:
		vec3<double> horizontal;
		vec3<double> vertical;
		vec3<double> lcorner;
		vec3<double> origin;
	};
}
