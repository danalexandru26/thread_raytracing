#include"Ray.hpp"

namespace math
{
	ray::ray()
		:direction{}, origin{}
	{}

	ray::ray(vec3<double> direction)
		: direction{direction}, origin{}
	{}

	ray::ray(vec3<double> origin, vec3<double> direction)
		: origin{origin}, direction{direction}
	{}

	vec3<double> ray::at(double t) const
	{
		return origin + direction * t;
	}
}