#pragma once

#include"../Vector/Vector.hpp"

namespace math {
	struct ray
	{
		ray();
		ray(vec3<float> direction);
		ray(vec3<float> direction, vec3<float> origin);

		vec3<float> at(float t) const;

		vec3<float> direction;
		vec3<float> origin;
	};
}