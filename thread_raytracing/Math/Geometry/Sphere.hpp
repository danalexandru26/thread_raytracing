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
			sphere(double radius, vec3<double> center, std::shared_ptr<material> mat);

			virtual bool hit(const ray& r, double min, double max, record& rec) const;

		private:
			double radius;
			vec3<double> center;
			std::shared_ptr<material> mat;
		};
	}
}