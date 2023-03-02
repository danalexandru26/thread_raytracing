#include"Sphere.hpp"


namespace math
{
	namespace geometry
	{
		sphere::sphere()
			:radius{}, center{}
		{}

		sphere::sphere(double radius, vec3<double> center, std::shared_ptr<material> mat)
			:radius{radius}, center{center}, mat{mat}
		{}

		bool sphere::hit(const ray& r, double min, double max, record& rec) const
		{
			auto ac = r.origin - center;

			auto a = r.direction.length_squared();
			auto b = dot(r.direction, ac);
			auto c = ac.length_squared() - radius * radius;

			auto delta = b * b - a * c;
			if (delta < 0) {
				return false;
			}

			auto delta_s = std::sqrt(delta);
			auto root = (- b - delta_s) / a;

			if (root < min || root > max) {
				root = (-b + delta_s) / a;
				if (root < min || root > max) {
					return false;
				}
			}

			rec.temp = root;
			rec.point = r.at(root);
			auto c_normal = (rec.point - center) / radius;
			rec.set_normal(r, c_normal);
			rec.mat = mat;

			return true;
		}
	}
}