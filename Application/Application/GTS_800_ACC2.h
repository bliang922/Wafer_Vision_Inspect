#pragma once

#include "gts.h"
#include <string>
#include <stdbool.h>
#include "Time_Counter.h"
#include <thread>

#define AXIS_NUM 2
#define AXIS1_LOAD 1
#define AXIS2_ROTATE 2
#define SEARCH_HOME		-200000
#define HOME_OFFSET		-200
#define LOAD_OFFSET		-2000
#define MEASURE_OFFSET		-2000

class GTS_800_ACC2
{
public:
	GTS_800_ACC2(char * deviceName, Time_Counter *timer, int timeOut);
	char *device_name;
	bool error;
	short rt, capture;

	const char* errorDiscript;
	TTrapPrm trapPrm;
	TJogPrm jog;

	long status, pos;
	double prfPos, encPos, axisPrfPos, axisEncPos;


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

	bool initialize();
	void close();
	//每个扫描周期需要处理的逻辑，根据输入变化更新输出信号
	void run();
	void homePosition(short axis);
	void MoveToPos(short axis,double position, double velocity);
	void measurePosition();
	void jogIncrease();
	void jogDecrease();


};

