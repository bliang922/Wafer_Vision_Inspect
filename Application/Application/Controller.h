#pragma once

#include <QObject>
#include <QtWidgets>

#include <thread>
#include <mutex>
#include "Valve.h"
#include "Time_Counter.h"
#include <string>
#include <stdbool.h>
#include "Axis.h"

#define INPUT_NUM 16
#define OUTPUT_NUM 16
#define AXIS_NUM         2
#define AXIS1_LOAD       1
#define AXIS2_ROTATE     2

#define LOAD_POSITION		250000
#define MEASURE_POSITION  50000
#define LOAD_UNLOAD_VELOCITY 50
#define ROTATE_VELOCITY 50

class Controller : public QObject
{
	Q_OBJECT

public:
	Controller(QObject *parent);
	~Controller();

public:
	bool Input[INPUT_NUM];
	bool Output[OUTPUT_NUM];
	bool myInputLogic[INPUT_NUM];
	bool myOutputLogic[OUTPUT_NUM];
	// 通用输入读取值
	long lGpiValue;
	bool error = 0;
	int rt = 0;

	std::thread controllerThread;
	std::mutex* mtx;
	QTextEdit *textEdit;
	Axis *axis[AXIS_NUM];
	bool gts_800_Connected = false;
	bool AUTO_MODE = false;
	bool initialize();
	void lauchControllerThread();
	void IORefresh();
	void logic_Circle();
	void close();
	void jogIncrease(short axis);

	//field device:
	bool start_button1 = false;
	bool start_button2 = false;
	bool home_button = false;
	bool moveToLoad_button = false;
	bool moveToMeasure_button = false;

	bool pc_done = false;
	bool Buzzor_on = false;
	bool Vaccum_on = false;

	bool step1_loadPart = false;
	bool step2_reload = false;
	Valve *solenoid_rotateStation;
	Time_Counter timer[10];

signals:
	void loadPartDone();
	void HMI_update();
	void raiseAlarm(const char*, const char*);

};

