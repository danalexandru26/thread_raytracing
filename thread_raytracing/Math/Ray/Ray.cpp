#include"Ray.hpp"

namespace math
{
	ray::ray()
		:direction{}, origin{}
	{}

	ray::ray(vec3<float> direction)
		: direction{direction}, origin{}
	{}

	ray::ray(vec3<float> origin, vec3<float> direction)
		: origin{origin}, direction{direction}
	{}

	vec3<float> ray::at(float t) const
	{
		return origin + direction * t;
	}
}