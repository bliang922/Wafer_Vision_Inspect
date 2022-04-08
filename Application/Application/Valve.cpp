#include "Valve.h"

//constructor
Valve::Valve(char * deviceName, Time_Counter *timer, int timeOut) {

	this->device_name = deviceName;
	this->timer = timer;
	this->timeOut_ms = timeOut;
	this->timer->interval_s = this->timeOut_ms / 1000;

}

//logic caculation in circulation
void Valve::run() {


	//detect cmdopen action
	if (cmdOpen && !previous_cmdOpen && !cmdClose && !error) {
		this->timer->start();
		previous_cmdOpen = true;
		out_open = true;
		out_close = false;
	}

	if (cmdOpen && in_opened && timer->started) timer->started = false;

	//detect command close action
	if (cmdClose == true && previous_cmdClose == false && !cmdOpen && !error) {
		this->timer->start();
		previous_cmdClose = true;
		out_open = false;
		out_close = true;

	}

	if (cmdClose && in_closed && timer->started) timer->started = false;


	//if there is error, due to time out or from field
	if (timer->timeOut || in_error) {
		error = true;
		out_open = false;
		out_close = false;
	}

	if (cmdReset) {
		timer->timeOut = false;
		error = false;
		errorStored = false;
		out_open = false;
		out_close = false;
		cmdReset = false;
	}

	//tick the time clock
	if (timer->started) {
		timer->run();
	}

	previous_cmdOpen = cmdOpen;
	previous_cmdClose = cmdClose;
}
