#include "Time_Counter.h"
using namespace std::chrono;

void Time_Counter::start() {
	t1 = steady_clock::now();
	started = true;
	timeOut = false;
}

void Time_Counter::run() {
	if (this->started) {
		t2 = steady_clock::now();
		std::chrono::duration<double> diff = (t2 - t1);

		if (diff.count() > interval_s)
			timeOut = true, started = false;

	}
}
