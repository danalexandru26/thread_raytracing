#ifndef THREAD_JOINER
#define THREAD_JOINER

#include<vector>
#include<thread>

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



#endif



