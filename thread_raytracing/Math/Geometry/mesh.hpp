#pragma once

#include"../Vector/Vector.hpp"
#include"../Ray/Ray.hpp"

namespace math
{
	namespace geometry
	{


		struct record;

		class material {
		public:
			virtual bool scatter(const ray& in, const record& rec, vec3<double>& attenuation, ray& out) const = 0;
		};

				class lambertian : public material {
		public:
			lambertian(const vec3<double>& attenuation);

			virtual bool scatter(const ray& in, const record& rec, vec3<double>& attenuation, ray& out) const;


		private:
			vec3<double> albedo;
		};

		class metal : public material {
		public:
			metal(const vec3<double>& attenuation);

			virtual bool scatter(const ray& in, const record& rec, vec3<double>& attenuation, ray& out) const;

		private:
			vec3<double> albedo;
		};


		struct record
		{
			vec3<double> point;
			vec3<double> normal;
			std::shared_ptr<material> mat;

			double temp;
			bool face;

			void set_normal(const ray& r, vec3<double>& c_normal);
		};

		class mesh
		{
		public:
			virtual bool hit(const ray& r, double min, double max, record& rec) const = 0;
		};
	}
}