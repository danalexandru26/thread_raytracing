#include"Sphere.hpp"


namespace math
{
	namespace geometry
	{
		sphere::sphere()
			:radius{}, center{}
		{}

		sphere::sphere(float radius, vec3<float> center)
			:radius{radius}, center{center}
		{}

		bool sphere::hit(const ray& r, float min, float max, record& rec) const
		{
			auto ac = r.origin - center;

			auto a = r.direction.length_squared();
			auto b = dot(r.direction, ac);
			auto c = ac.length_squared() - radius * radius;

			auto delta = b * b - a * c;
			if (delta < 0)
			{
				return false;
			}

			auto delta_s = std::sqrt(delta);
			auto root = (- b - delta_s) / a;

			if (root < min || root > max)
			{
				root = (-b + delta_s) / a;
				if (root < min || root > max)
				{
					return false;
				}
			}

			rec.temp = root;
			rec.point = r.at(root);
			auto c_normal = (rec.point - center) / radius;
			rec.set_normal(r, c_normal);

			return true;
		}
	}
}