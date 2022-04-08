#include "Controller_IOC0640.h"

Controller_IOC0640::Controller_IOC0640(QObject *parent)
	: QObject(parent)
{

}

Controller_IOC0640::~Controller_IOC0640()
{
}

void Controller_IOC0640::initialize() {

	//控制卡的初始化操作
	if (ioc_board_init() <= 0)
		this->textEdit->append("IOC0640 initialize failed");
	else
		ioc0640_Connected = TRUE;

	solenoid_rotateStation.timer = &timer[0];
	solenoid_rotateStation.timer->interval_ms = 3000;

}


void Controller_IOC0640::lauchIORefreshThread() {

	thread_io_refresh = std::thread(&Controller_IOC0640::logic_Circle, this);
	thread_io_refresh.detach();
}

void Controller_IOC0640::close() {
	ioc0640_Connected = false;
	ioc_board_close();
}

void Controller_IOC0640::IORefresh() {


		if (mtx->try_lock()) {

			//read inputs from 0640 IO module
			for (int i = 0; i < INPUT_NUM; i++) {
				Input[i] = ioc_read_inbit(0, i + 1);
			}

			//write outputs to 0640 IO module
			for (int i = 0; i < OUTPUT_NUM; i++) {
				ioc_write_outbit(0, i + 1, Output[i]);
			}

			mtx->unlock();
		}

}

void Controller_IOC0640::logic_Circle() {

	while (1) {
		
		if (!ioc0640_Connected) break;

/*******************************************Fresh IO Image*******************************************************************/

		IORefresh();

		/*connect electric IO to device program variables
		IN1 Start Button            ----> Input[0]
		IN3 rotate station position1----> Input[2]
		IN4 rotate station position2----> Input[3]
		OUT1 light                  ----> Output[0]
		OUT2 LED1					----> Output[1]
		OUT3 LED2				    ----> Output[2]
		OUT4 valve1                 ----> Output[3]
		OUT5 valve2                 ----> Output[4]*/
		start_button = Input[0];
		solenoid_rotateStation.in_closed = Input[2];
		solenoid_rotateStation.in_opened = Input[3];

		Output[0] = light_on;
		Output[1] = led1_on;
		Output[2] = led2_on;
		Output[3] = solenoid_rotateStation.out_open;
		Output[4] = solenoid_rotateStation.out_close;

		//time counter caculating
		for (int i = 0; i < 10; i++) {
			timer[i].run();
		}


/*******************************************logic block*******************************************************************/

		//step1:open valve to load part
		if (start_button && !step1_loadPart && !step2_reload && pc_done && solenoid_rotateStation.in_closed)
			step1_loadPart = true;

		if (step1_loadPart) {
			if (!solenoid_rotateStation.error&&solenoid_rotateStation.in_closed)
				solenoid_rotateStation.cmdOpen = true, led2_on = false;
			if (solenoid_rotateStation.in_opened&&pc_done) {
				led1_on = true;
				step1_loadPart = false;
				pc_done = false;
				emit loadPartDone();
			}
			solenoid_rotateStation.run();
		}

		//step2: close valve to reload part
		if (start_button && !step1_loadPart && !step2_reload && pc_done && solenoid_rotateStation.in_opened)
			step2_reload = true;

		if (step2_reload&&pc_done) {
			if (!solenoid_rotateStation.error&&solenoid_rotateStation.in_opened)
				solenoid_rotateStation.cmdOpen = false, led1_on = false;
			if (solenoid_rotateStation.in_closed&&pc_done) {
				led2_on = true;
				step2_reload = false;
				pc_done = false;
				emit loadPartDone();
			}
			solenoid_rotateStation.run();

		}

/*******************************************Circulation Frequency Setting*******************************************************************/

		std::this_thread::sleep_for(std::chrono::milliseconds(200));

	}
}
