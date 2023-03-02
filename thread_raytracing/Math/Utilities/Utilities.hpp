#pragma once

#include<random>

namespace utilities
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
}