#include"mesh.hpp"
#include <random>

namespace math
{
	double random_double()
	{
		static std::uniform_real_distribution<double> distribution(0.0, 1.0);
		static std::mt19937 generator;

		return distribution(generator);
	}

	double random_double(double minimum, double maximum)
	{
		return minimum + (maximum - minimum) * random_double();
	}

	double clamp(double value, double min, double max)
	{
		if (value < min)
		{
			return min;
		}
		if (value > max)
		{
			return max;
		}
		return value;
	}

	vec3 <double> random() {
		return vec3<double>(random_double(), random_double(), random_double());
	}

	vec3<double> random(double minimum, double maximum) {
		return vec3<double>(random_double(minimum, maximum), random_double(minimum, maximum), random_double(minimum, maximum));
	}

	vec3<double> random_in_sphere() {
		while (true) {
			auto vec = random(-1.0, 1.0);
			if (vec.length_squared() >= 1)continue;
			return vec;
		}
	}

	vec3<double> random_unit_vector() {
		return unit(random_in_sphere());
	}

	namespace geometry
	{

		void record::set_normal(const ray& r, vec3<double>& c_normal)
		{
			if (dot(r.direction, c_normal) > 0.0f)
			{
				face = false;
				normal = -c_normal;
			}
			else
			{
				face = true;
				normal = c_normal;
			}
		}

		lambertian::lambertian(const vec3<double>& albedo) :
			albedo{ albedo }
		{}

		bool lambertian::scatter(const ray& in, const record& rec, vec3<double>& attenuation, ray& out) const {
			auto direction = rec.normal + random_unit_vector();

			if (direction.near_zero()) {
				direction = rec.normal;
			}

			out = ray(rec.point, direction);
			attenuation = albedo;

			return true;
		}
		
		metal::metal(const vec3<double>& attenuation) :
			albedo{ attenuation }
		{}

		bool metal::scatter(const ray& in, const record& rec, vec3<double>& attenuation, ray& out) const {
			vec3<double> reflected = reflect(unit(in.direction), rec.normal);
			out = ray(rec.point, reflected);
			attenuation = albedo;

			return (dot(out.direction, rec.normal) > 0);
		}
	}
}