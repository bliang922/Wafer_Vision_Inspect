#pragma once
#include <chrono>
#include <stdbool.h>

class Time_Counter
{
public:
	std::chrono::steady_clock::time_point t1, t2;     // start timer
	bool timeOut = false;
	bool started = false;

	void run();
	void start();
	double interval_s;

};
