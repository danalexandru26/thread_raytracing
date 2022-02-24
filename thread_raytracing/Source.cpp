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

using namespace math;
using namespace render;

template<typename T>
class threadsafe_queue
{
private:
	mutable std::mutex mut;
	std::queue<std::shared_ptr<T> > data_queue;
	std::condition_variable data_cond;
public:
	threadsafe_queue()
	{}
	void wait_and_pop(T& value)
	{
		std::unique_lock<std::mutex> lk(mut);
		data_cond.wait(lk, [this] {return !data_queue.empty(); });
		value = std::move(*data_queue.front());
		data_queue.pop();
	}
	bool try_pop(T& value)
	{
		std::lock_guard<std::mutex> lk(mut);
		if (data_queue.empty())
			return false;
		value = std::move(*data_queue.front());
		data_queue.pop();
		return true;
	}
	std::shared_ptr<T> wait_and_pop()
	{
		std::unique_lock<std::mutex> lk(mut);
		data_cond.wait(lk, [this] {return !data_queue.empty(); });
		std::shared_ptr<T> res = data_queue.front();
		data_queue.pop();
		return res;
	}
	std::shared_ptr<T> try_pop()
	{
		std::lock_guard<std::mutex> lk(mut);
		if (data_queue.empty())
			return std::shared_ptr<T>();
		std::shared_ptr<T> res = data_queue.front();
		data_queue.pop();
		return res;
	}
	void push(T new_value)
	{
		std::shared_ptr<T> data(
			std::make_shared<T>(std::move(new_value)));
		std::lock_guard<std::mutex> lk(mut);
		data_queue.push(data);
		data_cond.notify_one();
	}
	bool empty() const
	{
		std::lock_guard<std::mutex> lk(mut);
		return data_queue.empty();
	}
};

class join_threads
{
public:
	explicit join_threads(std::vector<std::thread>& threads)
		:threads{ threads }
	{}

	~join_threads()
	{
		for (auto& thread : threads)
		{
			if (thread.joinable())
			{
				thread.join();
			}
		}
	}
private:
	std::vector<std::thread>& threads;
};

class function_wrapper
{
	struct impl_base
	{
		virtual void call() = 0;
		virtual ~impl_base() {}
	};
	std::unique_ptr<impl_base> impl;

	template<typename F>
	struct impl_type : impl_base
	{
		F f;
		impl_type(F&& f) : f(std::move(f)) {}
		void call() { f(); }
	};
public:
	template<typename F>
	function_wrapper(F&& f)
		:impl(new impl_type<F>(std::move(f)))
	{}

	void operator () () { impl->call(); }

	function_wrapper() = default;

	function_wrapper(function_wrapper&& other)
		:impl(std::move(other.impl))
	{}

	function_wrapper& operator = (function_wrapper&& other)
	{
		impl = std::move(other.impl);
		return *this;
	}

	function_wrapper(const function_wrapper&) = delete;
	function_wrapper(function_wrapper&) = delete;
	function_wrapper& operator=(const function_wrapper&) = delete;
};

class thread_pool
{
	threadsafe_queue<function_wrapper> work_queue;
	std::atomic_bool done;
	std::vector<std::thread> threads;
	join_threads joiner;

	void worked_thread()
	{
		while (!done)
		{
			function_wrapper task;
			if (work_queue.try_pop(task))
			{
				task();
			}
			else
			{
				std::this_thread::yield();
			}
		}
	}
public:
	thread_pool()
		:done(false), joiner(threads)
	{
		auto thread_count = std::thread::hardware_concurrency();

		try
		{
			for (auto i = 0; i < thread_count; ++i)
			{
				threads.push_back(std::thread(&thread_pool::worked_thread, this));
			}
		}
		catch (...)
		{
			done = true;
			throw;
		}
	}

	~thread_pool()
	{
		done = true;
	}

	template<typename FunctionType, typename... Args >
	std::future<void> submit(FunctionType f, Args&&... args)
	{
		std::packaged_task<void()> task(std::bind(f, std::forward<Args>(args)...));
		std::future<void> result(task.get_future());
		work_queue.push(std::move(task));

		return result;
	}
};

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