#pragma once
#include "Time_Counter.h"
#include <string>
#include <stdbool.h>

class Valve
{
public:
	Valve(char * deviceName, Time_Counter *timer, int timeOut);
	char *device_name;
	bool in_closed = false;
	bool in_opened = false;
	bool in_error = false;
	bool cmdOpen = false;
	bool cmdClose = false;

	bool cmdReset = false;
	int timeOut_ms;
	bool error = false;
	bool errorStored = false;
	bool out_close = false;
	bool out_open = false;
	bool previous_cmdOpen = false;
	bool previous_cmdClose = false;

	Time_Counter *timer;
	void run();
};
