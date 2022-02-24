#include"mesh.hpp"

namespace math
{
	namespace geometry
	{
		void record::set_normal(const ray& r, vec3<float>& c_normal)
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
	}
}