#include "Controller.h"

Controller::Controller(QObject *parent)
	: QObject(parent)
{
		axis[0] = new Axis("linerStation", AXIS1_LOAD);
		axis[1] = new Axis("rotateStation", AXIS2_ROTATE);

}

Controller::~Controller()
{

}

bool Controller::initialize() {
	// 如果指令执行返回值为非0，说明指令执行错误
	rt = 0;
	rt = GT_Open();
	if (rt) return false;
	rt = GT_Reset();
	if (rt) return false;

	//加载固高运动控制卡伺服轴配置文件
	//rt = GT_LoadConfig("config.cfg");
	rt = GT_LoadConfig("GTS800.cfg");
	if (rt) return false;
	rt = GT_ClrSts(1, 2);//使loadConfig指令生效
	//rt = GT_ZeroPos (1);
	//rt = GT_ZeroPos(2);
	//rt = GT_AxisOn(1);
	//rt = GT_AxisOn(2);
	axis[0]->vel_low = 30;
	axis[0]->vel_high = 50;
	axis[0]->vel_jog = 50;
	axis[0]->home_offset = AXIS1_HOME_OFFSET;
	axis[1]->vel_low = 3;
	axis[1]->vel_high = 5;
	axis[1]->vel_jog = 3;

	axis[1]->home_offset = AXIS2_HOME_OFFSET;
	if (axis[0]->initialize()) {
		this->textEdit->append(QString::QString("Liner station axis initialize success."));
	}
	else
	{
		this->textEdit->append(QString::QString("Liner station initialize failed."));
		raiseAlarm("Axis1", "Liner station initialize failed.");
	}

	if (axis[1]->initialize()) {
		this->textEdit->append(QString::QString("Rotate station axis initialize success."));
	}
	else
	{
		this->textEdit->append(QString::QString("Rotate station initialize failed."));
		raiseAlarm("Axis1", "Rotate station initialize failed.");
	}

	//initialize input to true, high input voltage 24V
	for (int i = 0; i < INPUT_NUM; i++) {
		Input[i] = false;
		myInputLogic[i] = false;
	}

	//initialize output to true, high output voltage 24V
	for (int i = 0; i < OUTPUT_NUM; i++) {
		Output[i] = false;
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
	for (int i = 0; i < AXIS_NUM; i++) {
		GT_AxisOff(i+1);

	}

}

/*******************************************Fresh IO Image*******************************************************************/

/*EXI0-- DI0--EStop
	EXI14--DI1--Start1
	EXI15--DI2--Start2
	EXO0--DO0--Buzzer
	EXO1--DO1--not connected
	EXO2--DO2--strobe
	EXO8--DO8--Vacumm

*/

void Controller::IORefresh() {

	   
	if (mtx->try_lock()) {

	//read inputs from gts_800 module
		for (int i = 0; i < INPUT_NUM; i++) {
			//Input[i] = ioc_read_inbit(0, i + 1);

				// 读取EXI3输入值
			GT_GetDi(MC_GPI, &lGpiValue);
			if (lGpiValue & (1 << i)) Input[i] = true;
			else Input[i] = false;
			myInputLogic[i] = !Input[i];

		}
		start_button1 = myInputLogic[14];
		start_button2 = myInputLogic[15];

		myOutputLogic[0] = Buzzor_on;
		myOutputLogic[8] = Vaccum_on;
		myOutputLogic[2] = strobe_on;

		//write outputs to gts_800 module
		for (int i = 0; i < OUTPUT_NUM; i++) {
			//ioc_write_outbit(0, i + 1, Output[i]);

				// EXO6输出高电平，使指示灯灭
			Output[i] = !myOutputLogic[i];

			GT_SetDoBit(MC_GPO,i, Output[i]);

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

		if (start_button1&&start_button2) AUTO_MODE = true;
		//step1:move linear station to measure position
		axis[AXIS1_LOAD]->error = axis[AXIS1_LOAD]->status & 0x02;
		axis[AXIS2_ROTATE]->error = axis[AXIS2_ROTATE]->status & 0x02;

		if (AUTO_MODE&&start_button1&&start_button2 && !step1_loadPart && !step2_reload && pc_done&&!axis[AXIS1_LOAD]->error)
			step1_loadPart = true;

		if (step1_loadPart) {
			
			axis[AXIS1_LOAD]->MoveToPos(MEASURE_POSITION, LOAD_UNLOAD_VELOCITY);
			axis[AXIS1_LOAD]->in_measure_pos = true;
			axis[AXIS1_LOAD]->in_load_pos = false;

			this->textEdit->append(QString::QString("Liner station in MEASURE position"));

			//wait for machanical stable
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			step1_loadPart = false;
			emit loadPartDone();

		}

		////step2: move linear station to load position
		//if (AUTO_MODE && start_button1&&start_button2 && !step1_loadPart && !step2_reload && pc_done&&axis[AXIS1_LOAD]->in_measure_pos)
		//	step2_reload = true;

		//if (step2_reload&&pc_done) {
		//	axis[AXIS1_LOAD]->MoveToPos(LOAD_POSITION, LOAD_UNLOAD_VELOCITY);
		//	axis[AXIS1_LOAD]->in_measure_pos = false;
		//	axis[AXIS1_LOAD]->in_load_pos = true;

		//	//wait for machanical stable
		//	std::this_thread::sleep_for(std::chrono::milliseconds(500));
		//	step2_reload = false;
		//	this->textEdit->append(QString::QString("Liner station in LOAD position"));
		//}


/*******************************************Circulation Frequency Setting*******************************************************************/
		axis[0]->run();
		axis[1]->run();
		emit HMI_update();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

	}
}

void Controller::jogIncrease(short axisNum) {

	axis[axisNum]->jogIncrease();
}
