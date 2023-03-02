#include<iostream>
#include<fstream>

#include<thread>
#include<future>
#include<mutex>

#include<queue>

#include"Math/Vector/Vector.hpp"
#include"Math/Camera/Camera.hpp"
#include"Math/Container/List.hpp"
#include"Math/Container/Block.hpp"
#include"Math/Utilities/Utilities.hpp"

#include"Render/Coloring.hpp"
#include"Render/Render.hpp"

#include"Parallel/parallel_api.hpp"

using namespace math;
using namespace utilities;
using namespace render;

constexpr int reflections = 10;
constexpr int msaa_samples = 100;
constexpr float ratio = 16.0f / 9.0f;
constexpr int height = 500;
constexpr int width = static_cast<int>(height * ratio);

void work_sequential(vec3<double>* pixels);
void work_blocks(int loc_i, int loc_j, int m);
void work_stripes(int m);

camera cam(2.0, 16.0 / 9.0 * 2.0, 1.0);
list world;

std::vector<block> tiles(144, block(14400));
std::vector<block> tiles_s(height, block(width));

int main()
{
	thread_pool pool;

	auto metal_mat = std::make_shared<metal>(vec3<double>(0.8, 0.8, 0.8));
	auto metal_mat2 = std::make_shared<metal>(vec3<double>(0.8, 0.5, 0.5));
	auto lambertian_mat = std::make_shared<lambertian>(vec3<double>(0.8));

	world.add(std::make_shared<sphere>(0.2, vec3<double>(0.3, -0.3, -1.0), metal_mat));
	world.add(std::make_shared<sphere>(0.1, vec3<double>(0.7, -0.4, -1.0), metal_mat2));
	world.add(std::make_shared<sphere>(100.0, vec3<double>(0.0, -100.5, -1.0), lambertian_mat));
	//world.add(std::make_shared<sphere>(0.5f, vec3<float>(0.1f, 8.0f, -1.0f)));
	//world.add(std::make_shared<sphere>(0.25f, vec3<float>(0.2f, 10.0f, -1.0f)));


	vec3<double>* pixels = new vec3<double>[width * height];
	std::vector<std::future<void>> futures(height);

	for (auto i = 0; i < height; i++)
	{
		futures[i] = pool.submit(work_stripes, i);
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(500));
		
	for (auto& future : futures)
	{
		future.get();
	}

	std::cout << "P3\n" << width << ' ' << height << "\n255\n";

	for (auto i = height - 1; i >= 0; --i)
	{
		for (auto j = width - 1; j >= 0; --j)
		{
			color(std::cout, tiles_s[i].chunk[j], msaa_samples);
		}
	}
	return 0;
}

void work_stripes(int m)
{
	for (auto j = 0; j < width; ++j)
	{
		auto pixel = vec3<double>(0.0);
		for (auto k = 0; k < msaa_samples; ++k)
		{
			auto u = (m + random_double()) / (height - 1.0);
			auto v = (j + random_double()) / (width - 1.0);

			auto r = cam.emit(u, v);
			pixel += compute(r, world, reflections);
		}
		tiles_s[m].chunk[j] = pixel;
	}
}

void work_blocks(int loc_i, int loc_j, int m)
{
	auto count = -1;
	for (auto i = 0; i < 120; i++)
	{
		for (auto j = 0; j < 120; j++)
		{
			auto pixel = vec3<double>(0.0);
			for (auto k = 0; k < 100; k++)
			{
				auto u = (loc_i * 120 + i + random_double()) / (height - 1.0);
				auto v = (loc_j * 120 + j + random_double()) / (width - 1.0);

				auto r = cam.emit(u, v);
				pixel += compute(r, world, reflections);
			}
			tiles[m].chunk[++count] = pixel;
		}
	}
}
void work_sequential(vec3<double>* pixels)
{
	for (auto i = 0; i < height; ++i)
	{
		for (auto j = 0; j < width; ++j)
		{
			auto pixel = vec3<double>(0.0f);
			for (auto k = 0; k < msaa_samples; ++k)
			{
				auto u = (i + random_double()) / (height - 1.0f);
				auto v = (j + random_double()) / (width - 1.0f);

				auto r = cam.emit(u, v);
				pixel += compute(r, world, reflections);
			}
			pixels[i * width + j] = pixel;
		}
	}
}