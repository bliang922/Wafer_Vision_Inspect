#pragma once
#include "Time_Counter.h"
class Valve
{
public:
	bool in_closed;
	bool in_opened;
	bool cmdOpen;
	bool cmdReset;
	int timeOut_ms;
	bool error;
	bool out_close;
	bool out_open;

	Time_Counter *timer;
	void run();
};

