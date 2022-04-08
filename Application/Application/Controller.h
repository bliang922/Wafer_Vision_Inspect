#pragma once

#include <QObject>
#include <QtWidgets>
#include "IOC0640.H"

#include <thread>
#include <mutex>
#include "Valve.h"
#include "Time_Counter.h"
#include <string>
#include <stdbool.h>

#define INPUT_NUM 32
#define OUTPUT_NUM 32


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


	std::thread controllerThread;
	std::mutex* mtx;
	QTextEdit *textEdit;
	bool ioc0640_Connected = false;
	bool AUTO_MODE = false;
	void initialize();
	void lauchControllerThread();
	void IORefresh();
	void logic_Circle();
	void close();

	//field device:
	bool start_button = false;
	bool pc_done = false;
	bool light_on = false;
	bool led1_on = false;
	bool led2_on = false;
	bool step1_loadPart = false;
	bool step2_reload = false;
	Valve *solenoid_rotateStation;
	Time_Counter timer[10];

signals:
	void loadPartDone();
	void raiseAlarm(const char*, const char*);

};

