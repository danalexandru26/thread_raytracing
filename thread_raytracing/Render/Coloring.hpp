#pragma once

#include"../Math/Vector/Vector.hpp"

using namespace math;

namespace render {

	template<typename T>
	void color(std::ostream& os, vec3<T>& pixel)
	{
		auto scale = 1.0f / 100.0f;

		os << static_cast<int>(255.99 * clamp(pixel.x() * scale, 0.0f, 0.999f)) << ' ' << static_cast<int>(255.99 * clamp(pixel.y() * scale , 0.0f, 0.999f)) << ' ' << static_cast<int>(255.99 * clamp(pixel.z() * scale , 0.0f, 0.999f)) << '\n';
	}
}