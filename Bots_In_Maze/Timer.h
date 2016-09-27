#pragma once

#include <chrono>
//typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<__int64, std::ratio<1, 10000000> > > my_timer_type;

class Timer
{
public:
	void start_watch()
	{
		init = std::chrono::high_resolution_clock::now();
	}

	void stop_watch()
	{
		end = std::chrono::high_resolution_clock::now();
	}

	double get_time()
	{
		return std::chrono::duration<double, std::milli> (end - init).count();
	}
private:
	std::chrono::steady_clock::time_point  init;
	std::chrono::steady_clock::time_point  end;
};