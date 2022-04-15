#include "Controller.h"

Controller::Controller(QObject *parent)
	: QObject(parent)
{
	gts_800 = new GTS_800_ACC2("gts_800", &timer[0], 3000);

}

Controller::~Controller()
{

}

void Controller::initialize() {

	if (!gts_800->initialize()) {
		this->textEdit->append("gts_800 initialize failed");
		raiseAlarm("gts_800", "Initialize failed");

	}
	else {
		gts_800_Connected = true;
		//solenoid_rotateStation = new Valve((char*)"valve1", &timer[0], 5000);
		this->textEdit->append(QString::QString("gts_800 initialize success"));

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
	gts_800_Connected = false;
	gts_800->close();
}

/*******************************************Fresh IO Image*******************************************************************/

void Controller::IORefresh() {


	if (mtx->try_lock()) {

	//read inputs from gts_800 module
		for (int i = 0; i < INPUT_NUM; i++) {
			//Input[i] = ioc_read_inbit(0, i + 1);
			//myInputLogic[i] = !Input[i];

				// 读取EXI3输入值
			GT_GetDi(MC_GPI, &lGpiValue);
			if (lGpiValue & (1 << i)) Input[i] = true;
			else Input[i] = false;
		}
		start_button = myInputLogic[0];
		solenoid_rotateStation->in_closed = myInputLogic[3];
		solenoid_rotateStation->in_opened = myInputLogic[2];


		/*myOutputLogic[0] = light_on;
		myOutputLogic[1] = led1_on;
		myOutputLogic[2] = led2_on;
		myOutputLogic[3] = solenoid_rotateStation->out_open;
		myOutputLogic[4] = solenoid_rotateStation->out_close;*/


		//write outputs to gts_800 module
		for (int i = 0; i < OUTPUT_NUM; i++) {
			Output[i] = myOutputLogic[i];
			//ioc_write_outbit(0, i + 1, Output[i]);

				// EXO6输出高电平，使指示灯灭
			GT_SetDo(MC_GPO, Output[i] << i);
		}

		mtx->unlock();
	}

}


//the main body of the circulating logic
void Controller::logic_Circle() {

	while (1) {

		if (!gts_800_Connected) break;
		IORefresh();

//*******************************************logic block*******************************************************************/

		if (start_button) AUTO_MODE = true;
		//step1:move linear station to measure position
		if (AUTO_MODE&&start_button && !step1_loadPart && !step2_reload && pc_done&&gts_800->in_load_pos)
			step1_loadPart = true;

		if (step1_loadPart) {
			
			gts_800->MoveToPos(AXIS1_LOAD, MEASURE_POSITION, LOAD_UNLOAD_VELOCITY);
			gts_800->in_measure_pos = true;
			gts_800->in_load_pos = false;

			this->textEdit->append(QString::QString("Liner station in MEASURE position"));

			//wait for machanical stable
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			step1_loadPart = false;
			emit loadPartDone();

		}

		//step2: move linear station to load position
		if (AUTO_MODE && start_button && !step1_loadPart && !step2_reload && pc_done&&gts_800->in_measure_pos)
			step2_reload = true;

		if (step2_reload&&pc_done) {
			gts_800->MoveToPos(AXIS1_LOAD, LOAD_POSITION, LOAD_UNLOAD_VELOCITY);
			gts_800->in_measure_pos = false;
			gts_800->in_load_pos = true;

			//wait for machanical stable
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			step2_reload = false;
			this->textEdit->append(QString::QString("Liner station in LOAD position"));
		}


/*******************************************Circulation Frequency Setting*******************************************************************/
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

	}
}
