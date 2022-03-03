#pragma once

#include"../Math/Ray/Ray.hpp"
#include"../Math/Vector/Vector.hpp"

#include"../Math/Geometry/Sphere.hpp"
#include"../Math/Container/List.hpp"

using namespace math;
using namespace math::geometry;
using namespace math::geometry::container;

namespace render {

	vec3<float> compute(const ray& r, list& world)
	{
		record rec;

		if (world.hit(r, 0.0f, 10000000000.0f, rec))
		{
			return 0.5f * (rec.normal + vec3<float>(1.0f));
		}
		
		auto unitd = unit(r.direction);
		auto t = 0.5f * (unitd.y() + 1.0f);
		return (1.0f - t) * vec3<float>(1.0f, 1.0f, 1.0f) + t * vec3<float>(0.6f, 0.3f, 1.0f);
	}
}
