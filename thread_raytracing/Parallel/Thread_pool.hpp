#ifndef THREAD_POOL
#define THREAD_POOL

#include<thread>
#include<future>
#include<mutex>

#include"function_wrapper.hpp"
#include"parallel_queue.hpp"
#include"thread_joiner.hpp"


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


#endif