#pragma once

#include"../Vector/Vector.hpp"
#include"mesh.hpp"

namespace math
{
	namespace geometry
	{
		class sphere : public mesh
		{
		public:
			sphere();
			sphere(float radius, vec3<float> center);

			virtual bool hit(const ray& r, float min, float max, record& rec) const;

		private:
			float radius;
			vec3<float> center;
		};
	}
}