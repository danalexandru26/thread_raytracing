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

	float random_float(float min, float max)
	{
		return min + (max - min) * random_float();
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
}