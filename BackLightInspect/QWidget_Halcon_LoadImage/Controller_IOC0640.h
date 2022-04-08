#pragma once

#include <QObject>
#include "IOC0640.H"
#include <QtWidgets>
#include <thread>
#include <mutex>
#include "Valve.h"
#include "Time_Counter.h"

#define INPUT_NUM 32
#define OUTPUT_NUM 32


class Controller_IOC0640 : public QObject
{
	Q_OBJECT

public:
	Controller_IOC0640(QObject *parent);
	~Controller_IOC0640();

public:
	BOOL Input[INPUT_NUM];
	BOOL Output[OUTPUT_NUM];

	std::thread thread_io_refresh;
	std::mutex* mtx;
	QTextEdit *textEdit;
	bool ioc0640_Connected;

	void initialize();
	void lauchIORefreshThread();
	void IORefresh();
	void logic_Circle();
	void close();

	//field device:
	bool start_button;
	bool pc_done;
	bool light_on;
	bool led1_on;
	bool led2_on;
	bool step1_loadPart;
	bool step2_reload;
	Valve solenoid_rotateStation;
	Time_Counter timer[10];

signals:
	void loadPartDone();
};
