#pragma once

#include "gts.h"
#include <string>
#include <stdbool.h>
#include "Time_Counter.h"
#include <thread>
#include <stddef.h>
#define AXIS_NUM         2
#define AXIS1_LOAD       1
#define AXIS2_ROTATE     2
#define SEARCH_HOME		-200000
#define HOME_OFFSET		-200
#define LOAD_POSITION		-2000
#define MEASURE_POSITION  -2000
#define LOAD_UNLOAD_VELOCITY 10
#define ROTATE_VELOCITY 10

class GTS_800_ACC2
{
public:
	GTS_800_ACC2(const char * deviceName, Time_Counter *timer, int timeOut);
	const char *device_name;
	short rt, capture;

	const char* errorDiscript;
	TTrapPrm trapPrm;
	TJogPrm jog;

	long status, pos;
	double prfPos, encPos, axisPrfPos, axisEncPos;


	bool in_load_pos = false;
	bool in_measure_pos = false;
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
public:
	bool initialize();
	void close();
	//每个扫描周期需要处理的逻辑，根据输入变化更新输出信号
	void run();

	bool homePosition(short axis);
	bool MoveToPos(short axis,double position, double velocity);
	void measurePosition();
	void jogIncrease(short axis);
	void jogDecrease(short axis);
	void enableAxis(short axis);
};

