#pragma once

#include<random>

namespace math
{
	class timer
	{
	public:
		static void t_begin()
		{
			begin = std::chrono::high_resolution_clock::now();
		}

		static void t_end()
		{
			end = std::chrono::high_resolution_clock::now();
		}

		static decltype(auto) delta()
		{
			std::chrono::duration<float, std::milli> delta = begin - end;

			return delta;
		}

	private:
		static std::chrono::steady_clock::time_point begin;
		static std::chrono::steady_clock::time_point end;
	};

	float random_float()
	{
		static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
		static std::mt19937 generator;

		return distribution(generator);
	}

	float random_float(float minimum, float maximum)
	{
		return minimum + (maximum - minimum) * random_float();
	}

	float random_double() {
		static std::uniform_real_distribution<float> distribution_double(0.0f, 1.0f);
		static std::mt19937 generator_double;

		return distribution_double(generator_double);
	}

	float random_double(int minimum, int maximum) {
		return minimum + (maximum - minimum) * random_double();
	}

	float clamp(float value, float min, float max)
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

	vec3 <float> random() {
		return vec3<float>(random_float(), random_float(), random_float());
	}

	vec3<float> random(float minimum, float maximum) {
		return vec3<float>(random_float(minimum, maximum), random_float(minimum, maximum), random_float(minimum, maximum));
	}

	vec3<float> random_in_sphere() {
		while (true) {
			auto vec = random(-1, 1);
			if (vec.length_squared() >= 1)continue;
			return vec;
		}
	}
}