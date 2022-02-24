#include"List.hpp"

namespace math
{
	namespace geometry
	{
		namespace container
		{
			list::list()
			{}

			list::list(std::shared_ptr<mesh>& object)
			{
				add(object);
			}

			void list::add(std::shared_ptr<mesh> object)
			{
				objects.push_back(object);
			}

			bool list::hit(const ray& r, float min, float max, record& rec) const
			{
				record t_record;
				auto any_hit = false;
				auto closest = max;

				for (auto& object : objects)
				{
					if (object->hit(r, min, closest, t_record))
					{
						any_hit = true;
						closest = t_record.temp;
						rec = t_record;
					}
				}
				return any_hit;
			}
		}
	}
}