#pragma once

#include"../Math/Ray/Ray.hpp"
#include"../Math/Vector/Vector.hpp"

#include"../Math/Geometry/Sphere.hpp"
#include"../Math/Container/List.hpp"

using namespace math;
using namespace math::geometry;
using namespace math::geometry::container;

namespace render {

	vec3<double> compute(const ray& r, list& world, int reflections)
	{
		record rec;
		if (reflections <= 0)return vec3<double>(0.0);

		if (world.hit(r, 0.0, 10000000000.0, rec)) {
			ray scatter;
			vec3<double> attenuation;

			if (rec.mat->scatter(r, rec, attenuation, scatter)) {
				return attenuation * compute(scatter, world, reflections - 1);
			}
			return vec3<double>(0.0);
		}
		
		auto unitd = unit(r.direction);
		auto t = 0.5 * (unitd.y() + 1.0);
		return (1.0 - t) * vec3<double>(1.0, 1.0, 1.0) + t * vec3<double>(0.5, 0.5, 0.7);
	}
}
