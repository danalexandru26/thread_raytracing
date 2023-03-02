#pragma once


#include<vector>
#include<memory>

#include"../Geometry/mesh.hpp"

namespace math
{
	namespace geometry
	{
		
		namespace container
		{
			class list : public mesh
			{
			public:
				list();
				list(std::shared_ptr<mesh>& object);

				void add(std::shared_ptr<mesh> object);

				bool hit(const ray& r, double min, double max, record& rec) const;

			private:
				std::vector<std::shared_ptr<mesh>> objects;
			};
		}
	}
}