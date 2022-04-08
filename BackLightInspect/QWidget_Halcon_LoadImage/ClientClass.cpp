#include "ClientClass.h"

ClientClass::ClientClass(QObject *parent)
	: QObject(parent)
{
}

ClientClass::~ClientClass()
{
}

void ClientClass::initialize()
{
	int s = -1;
	ZeroMemory(sendbuf, sizeof(sendbuf));
	ZeroMemory(recvbuf, sizeof(recvbuf));

	ctx = modbus_new_tcp("127.0.0.1", 1502);

	modbus_set_debug(ctx, TRUE);

	modbus_set_error_recovery(ctx, MODBUS_ERROR_RECOVERY_LINK);
	modbus_set_error_recovery(ctx, MODBUS_ERROR_RECOVERY_PROTOCOL);


	if (modbus_connect(ctx) == -1) {
		textEdit->append(QString("Connection failed")+ modbus_strerror(errno));
		modbus_free(ctx);
		return;
	}
	modbusConnected = true;

}

void  ClientClass::lauchCommThread() {
	MbCommThread = std::thread(&ClientClass::cyclicComm_PLC, this);
	MbCommThread.detach();

}

void  ClientClass::cyclicComm_PLC() {
	while (1) {
		if (mtx->try_lock()) {

			memcpy(old_recvbuf, recvbuf, sizeof(recvbuf));
			//	strcpy((char *)sendbuf, "this is a cyclic data from client\n");

			rc = modbus_write_registers(ctx, WRITE_PLC_HOLDING_REGISTER_START_ADDRESS,
				WRITE_PLC_HOLDING_REGISTER_LEN, sendbuf);
			//rc = modbus_write_registers(ctx, 1,
			//		1, sendbuf);
			if (rc != WRITE_PLC_HOLDING_REGISTER_LEN) {
				textEdit->append(QString("ERROR modbus_write_registers ") + rc);
			}
			rc = modbus_read_registers(ctx, READ_PLC_HOLDING_REGISTER_START_ADDRESS,
				READ_PLC_HOLDING_REGISTER_LEN, recvbuf);
			if (rc != READ_PLC_HOLDING_REGISTER_LEN) {
				textEdit->append(QString("ERROR modbus_read_registers ")+rc);
			}

			mtx->unlock();

		}

		//if read data from PLC changed, emit valueChanged signal to MainUI
		if (old_recvbuf[0] != recvbuf[0]) {
			emit valueChanged();
		}

		emit plcDataUpdate();

		std::this_thread::sleep_for(std::chrono::milliseconds(200));

	}

}

