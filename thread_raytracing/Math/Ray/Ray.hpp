#pragma once

#include"../Vector/Vector.hpp"

namespace math {
	struct ray
	{
		ray();
		ray(vec3<double> direction);
		ray(vec3<double> origin, vec3<double> direction);

		vec3<double> at(double t) const;

		vec3<double> direction;
		vec3<double> origin;
	};
}