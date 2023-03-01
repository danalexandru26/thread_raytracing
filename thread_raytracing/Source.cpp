#include<iostream>
#include<fstream>

#include<thread>
#include<future>
#include<mutex>

#include<queue>

#include"Math/Vector/Vector.hpp"
#include"Math/Camera/Camera.hpp"
#include"Math/Container/List.hpp"
#include"Math/Utilities/Utilities.hpp"

#include"Render/Coloring.hpp"
#include"Render/Render.hpp"

#include"Parallel/parallel_api.hpp"

using namespace math;
using namespace render;



struct block
{
	block()
	{
		chunk = std::vector < vec3<float>>();
	}

	block(int size)
	{
		chunk = std::vector<vec3<float>>(size);
	}

	std::vector<vec3<float>> chunk;
};

void work_sequential(vec3<float>* pixels);
void work_blocks(int loc_i, int loc_j, int m);
void work_stripes(int m);

const int samples = 100;
const float ratio = 16.0f / 9.0f;
const int height = 1440;
const int width = static_cast<int>(height * ratio);

camera cam(2.0f, 16.0f / 9.0f * 2.0f, 1.0f);
list world;

std::vector<block> tiles(144, block(14400));
std::vector<block> tiles_s(height, block(width));

int main()
{
	thread_pool pool;

	world.add(std::make_shared<sphere>(0.5f, vec3<float>(0.0f, 0.0f, -1.0f)));

	vec3<float>* pixels = new vec3<float>[width * height];
	std::vector<std::future<void>> futures(1440);

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

	for (auto i = 0; i < height; ++i)
	{
		for (auto j = 0; j < width; ++j)
		{
			color(std::cout, tiles_s[i].chunk[j]);
		}
	}
	return 0;
}

void work_stripes(int m)
{
	for (auto j = 0; j < width; ++j)
	{
		auto pixel = vec3<float>(0.0f);
		for (auto k = 0; k < samples; ++k)
		{
			auto u = (m + random_float()) / (height - 1.0f);
			auto v = (j + random_float()) / (width - 1.0f);

			auto r = cam.emit(u, v);
			pixel += compute(r, world);
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
			auto pixel = vec3<float>(0.0f);
			for (auto k = 0; k < 100; k++)
			{
				auto u = (loc_i * 120 + i + random_float()) / (height - 1.0f);
				auto v = (loc_j * 120 + j + random_float()) / (width - 1.0f);

				auto r = cam.emit(u, v);
				pixel += compute(r, world);
			}
			tiles[m].chunk[++count] = pixel;
		}
	}
}
void work_sequential(vec3<float>* pixels)
{
	for (auto i = 0; i < height; ++i)
	{
		for (auto j = 0; j < width; ++j)
		{
			auto pixel = vec3<float>(0.0f);
			for (auto k = 0; k < samples; ++k)
			{
				auto u = (i + random_float()) / (height - 1.0f);
				auto v = (j + random_float()) / (width - 1.0f);

				auto r = cam.emit(u, v);
				pixel += compute(r, world);
			}
			pixels[i * width + j] = pixel;
		}
	}
}