#pragma once

#include"../Math/Vector/Vector.hpp"

using namespace utilities;

namespace render {

	template<typename T>
	void color(std::ostream& os, vec3<T>& pixel, int msaa_samples)
	{
		auto scale = 1.0 / msaa_samples;

		//gamma correrction

		auto red = pixel.x();
		auto green = pixel.y();
		auto blue = pixel.z();

		auto gamma_red = std::sqrt(scale * red);
		auto gamma_green = std::sqrt(scale * green);
		auto gamma_blue = std::sqrt(scale * blue);


		os << static_cast<int>(255.99 * clamp(gamma_red, 0.0, 0.999)) << ' '
		   << static_cast<int>(255.99 * clamp(gamma_green, 0.0, 0.999)) << ' '
		   << static_cast<int>(255.99 * clamp(gamma_blue, 0.0, 0.999)) << '\n';
	}
}
