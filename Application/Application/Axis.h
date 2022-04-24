#pragma once

#include "gts.h"
#include <string>
#include <stdbool.h>
#include "Time_Counter.h"
#include <thread>
#include <stddef.h>

#define HOME_OFFSET		20000

class Axis
{
public:
	Axis(const char * deviceName, short axisNum);
	const char *device_name;
	short rt, capture, axisNum;

	const char* errorDiscript;
	TTrapPrm trapPrm;
	TJogPrm jog;
	THomePrm tHomePrm;
	THomeStatus tHomeSts;
	long status, pos;
	double prfPos, encPos, axisPrfPos, axisEncPos;

	bool enable = false;
	bool in_load_pos = false;
	bool in_measure_pos = false;
	bool in_error = false;
	bool step_p2p = false;
	bool step_p2p_done = false;

	bool step_home = false;
	bool in_home_pos = false;

	bool cmdReset = false;
	int timeOut_ms;
	bool error = false;
	bool errorStored = false;
	bool out_close = false;
	bool out_open = false;
	bool previous_cmdOpen = false;
	bool previous_cmdClose = false;

	Time_Counter timer;
public:
	bool initialize();
	//每个扫描周期需要处理的逻辑，根据输入变化更新输出信号
	void run();

	bool homePosition();
	bool MoveToPos(double position, double velocity);
	void jogIncrease();
	void jogDecrease();
	void enableAxis();
	void disableAxis();
	void jogStop();
	void reset();
};

