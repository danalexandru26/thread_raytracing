#pragma once

#include"../Vector/Vector.hpp"
#include"../Ray/Ray.hpp"

namespace math
{
	namespace geometry
	{
		struct record
		{
			vec3<float> point;
			vec3<float> normal;
			float temp;
			bool face;

			void set_normal(const ray& r, vec3<float>& c_normal);
		};

		class mesh
		{
		public:
			virtual bool hit(const ray& r, float min, float max, record& rec) const = 0;
		};
	}
}