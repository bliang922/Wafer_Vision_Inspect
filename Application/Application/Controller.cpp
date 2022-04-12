#include "Controller.h"

Controller::Controller(QObject *parent)
	: QObject(parent)
{

}

Controller::~Controller()
{
}

void Controller::initialize() {

	if (ioc_board_init() <= 0) {
		this->textEdit->append("IOC0640 initialize failed");
		raiseAlarm("IOC0640", "Initialize failed");

	}
	else {
		ioc0640_Connected = true;
		solenoid_rotateStation = new Valve((char*)"valve1", &timer[0], 5000);
		this->textEdit->append(QString::QString("IOC0640 initialize success"));

	}

	//initialize input to true, high input voltage 24V
	for (int i = 0; i < INPUT_NUM; i++) {
		Input[i] = true;
		myInputLogic[i] = false;
	}

	//initialize output to true, high output voltage 24V
	for (int i = 0; i < OUTPUT_NUM; i++) {
		Output[i] = true;
		myOutputLogic[i] = false;
	}

}


//start the controller thread
void Controller::lauchControllerThread() {

	controllerThread = std::thread(&Controller::logic_Circle, this);
	controllerThread.detach();
}

//close controller thread
void Controller::close() {
	ioc0640_Connected = false;
	ioc_board_close();
}

/*******************************************Fresh IO Image*******************************************************************/

void Controller::IORefresh() {


	if (mtx->try_lock()) {

		/*connect electric IO to device program variables
			IN1 Start Button            ----> Input[0]
			IN3 rotate station position1----> Input[2]
			IN4 rotate station position2----> Input[3]
			OUT1 light                  ----> Output[0]
			OUT2 LED1					----> Output[1]
			OUT3 LED2				    ----> Output[2]
			OUT4 valve1                 ----> Output[3]
			OUT5 valve2                 ----> Output[4]*/



			//read inputs from 0640 IO module
		for (int i = 0; i < INPUT_NUM; i++) {
			Input[i] = ioc_read_inbit(0, i + 1);
			myInputLogic[i] = !Input[i];
		}
		start_button = myInputLogic[0];
		solenoid_rotateStation->in_closed = myInputLogic[3];
		solenoid_rotateStation->in_opened = myInputLogic[2];


		myOutputLogic[0] = light_on;
		myOutputLogic[1] = led1_on;
		myOutputLogic[2] = led2_on;
		myOutputLogic[3] = solenoid_rotateStation->out_open;
		myOutputLogic[4] = solenoid_rotateStation->out_close;
		//write outputs to 0640 IO module
		for (int i = 0; i < OUTPUT_NUM; i++) {
			Output[i] = !myOutputLogic[i];
			ioc_write_outbit(0, i + 1, Output[i]);
		}

		mtx->unlock();
	}

}


//the main body of the circulating logic
void Controller::logic_Circle() {

	while (1) {

		if (!ioc0640_Connected) break;


		IORefresh();

		/*******************************************logic block*******************************************************************/

		if (start_button) AUTO_MODE = true;
		//step1:open valve to load part
		if (AUTO_MODE&&start_button && !step1_loadPart && !step2_reload && pc_done && solenoid_rotateStation->in_closed)
			step1_loadPart = true;

		if (step1_loadPart) {
			if (!solenoid_rotateStation->error && solenoid_rotateStation->in_closed)
				solenoid_rotateStation->cmdOpen = true, solenoid_rotateStation->cmdClose = false, led1_on = false;
			if (solenoid_rotateStation->in_opened) {
				led2_on = true;
				step1_loadPart = false;
				pc_done = false;
				light_on = false;
				this->textEdit->append(QString::QString("Rotate station in OPEN position"));
				IORefresh();
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));

				emit loadPartDone();
			}
		}

		//step2: close valve to reload part
		if (AUTO_MODE && start_button && !step1_loadPart && !step2_reload && pc_done && solenoid_rotateStation->in_opened)
			step2_reload = true;

		if (step2_reload&&pc_done) {
			if (!solenoid_rotateStation->error&&solenoid_rotateStation->in_opened)
				solenoid_rotateStation->cmdClose = true, solenoid_rotateStation->cmdOpen = false, led2_on = false;

			//after load part done, trigger camera
			if (solenoid_rotateStation->in_closed) {
				led1_on = true;
				step2_reload = false;
				pc_done = false;
				light_on = false;
				this->textEdit->append(QString::QString("Rotate station in CLOSE position"));
				IORefresh();
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				emit loadPartDone();
			}
		}

		if (solenoid_rotateStation->error && !solenoid_rotateStation->errorStored) {
			//this->textEdit->append(QString::QString(solenoid_rotateStation->device_name) + " time out error");
			raiseAlarm(solenoid_rotateStation->device_name, " time out error");
			solenoid_rotateStation->errorStored = true;
		}

		//while camera is not on, turn light on

		if (AUTO_MODE&&pc_done) light_on = true;




		/*******************************************Circulation Frequency Setting*******************************************************************/
		solenoid_rotateStation->run();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

	}
}
