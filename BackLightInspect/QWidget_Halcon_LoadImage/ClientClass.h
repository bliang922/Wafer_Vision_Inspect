#pragma once
#include "modbus.h"
#include <thread>
#include <mutex>
#include <QObject>
#include <errno.h>
#include <QtWidgets>

#define READ_PLC_HOLDING_REGISTER_START_ADDRESS 0
#define READ_PLC_HOLDING_REGISTER_LEN 50
#define WRITE_PLC_HOLDING_REGISTER_START_ADDRESS 50
#define WRITE_PLC_HOLDING_REGISTER_LEN 50

#define DEFAULT_PORT "502"

class ClientClass : public QObject
{
	Q_OBJECT

public:
	ClientClass(QObject *parent);
	~ClientClass();

	std::thread MbCommThread;
	std::mutex* mtx;
	modbus_mapping_t *mb_mapping;
	QTextEdit *textEdit;
	bool modbusConnected;
	uint16_t recvbuf[READ_PLC_HOLDING_REGISTER_LEN];
	uint16_t old_recvbuf[READ_PLC_HOLDING_REGISTER_LEN];
	uint16_t sendbuf[WRITE_PLC_HOLDING_REGISTER_LEN];
	modbus_t *ctx;
	int rc;

	void initialize();
	void lauchCommThread();
	void  cyclicComm_PLC();
signals:
	void valueChanged();
	void plcDataUpdate();
};



