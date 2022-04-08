#pragma once
#include <chrono>


class Time_Counter
{
public:
	std::chrono::steady_clock sc;   // create an object of `steady_clock` class
	std::chrono::time_point<std::chrono::steady_clock> start = sc.now();     // start timer
	void run();
	int interval_ms;

};

