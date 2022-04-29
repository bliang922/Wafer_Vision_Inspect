#include "Axis.h"

Axis::Axis(const char *device_name,short axisNum) {
	this->axisNum = axisNum;
	this->device_name = device_name;
}

bool Axis::initialize() {
	rt = 0;
	rt = GT_ZeroPos(axisNum);
	rt = GT_AxisOn(axisNum);
	if (!rt) enable = true;
	if(!homePosition()) rt=1;
	if (rt) return false;
	else return true;
}

bool Axis::homePosition() {

	////// 启动Home捕获
	//GT_SetCaptureMode(axisNum, CAPTURE_HOME);
	//// 切换到点位运动模式
	//GT_PrfTrap(axisNum);
	//// 读取点位模式运动参数
	//rt = GT_GetTrapPrm(axisNum, &trapPrm);
	//trapPrm.acc = 0.25;
	//trapPrm.dec = 0.25;
	//// 设置点位模式运动参数
	//rt = GT_SetTrapPrm(axisNum, &trapPrm);
	//// 设置点位模式目标速度，即回原点速度
	//rt = GT_SetVel(axisNum, 10);
	//// 设置点位模式目标位置，即原点搜索距离
	//rt = GT_SetPos(axisNum, SEARCH_HOME);
	//// 启动运动
	//rt = GT_Update(1 << (axisNum - 1));

	//do
	//{
	//	// 读取轴状态
	//	GT_GetSts(axisNum, &status);
	//	// 读取捕获状态
	//	GT_GetCaptureStatus(axisNum, &capture, &pos);
	//	// 读取规划位置
	//	GT_GetPrfPos(axisNum, &prfPos);
	//	// 读取编码器位置
	//	GT_GetEncPos(axisNum, &encPos);
	//	// 如果运动停止，返回出错信息
	//	if (0 == (status & 0x400))
	//	{
	//		error = true;
	//		errorDiscript = "Homing failed.";
	//		return false;
	//	}
	//	// 等待捕获触发
	//} while (0 == capture);


	//// 运动到"捕获位置+偏移量"
	//rt = GT_SetPos(axisNum, pos+HOME_OFFSET);
	//// 在运动状态下更新目标位置
	//rt = GT_Update(1 << (axisNum - 1));

	//do
	//{
	//	// 读取轴状态
	//	GT_GetSts(axisNum, &status);
	//	// 读取规划位置
	//	GT_GetPrfPos(axisNum, &prfPos);
	//	// 读取编码器位置
	//	GT_GetEncPos(axisNum, &encPos);
	//	// 等待运动停止
	//} while (status & 0x400);
	//// 检查是否到达"Home捕获位置+偏移量"
	//if (prfPos != pos + HOME_OFFSET)
	//{
	//	error = true;
	//	errorDiscript = "Axis move to position failed.";
	//	return false;
	//}
	//// 延时一段时间，等待电机停稳
	//std::this_thread::sleep_for(std::chrono::milliseconds(200));

	//// 位置清零
	//rt = GT_ZeroPos(axisNum);
	//// 读取规划位置
	//rt = GT_GetPrfPos(axisNum, &prfPos);
	//// 读取编码器位置
	//rt = GT_GetEncPos(axisNum, &encPos);
	//// 读取axis规划位置
	//rt = GT_GetAxisPrfPos(axisNum, &axisPrfPos);
	//// 读取axis编码器位置
	//rt = GT_GetAxisEncPos(axisNum, &axisEncPos);
	////return true;


	//GT_ClrSts(axisNum);
	//GT_SetPrfPos(axisNum, 0);
	//GT_AlarmOff(axisNum);
	//GT_LmtsOn(axisNum);
	//GT_Update(1 << (axisNum - 1));

	//GT_LmtSns(3);
	//GT_EncSns(1);
	//设置Smart Home回原点参数
	GT_GetHomePrm(axisNum, &tHomePrm);
	tHomePrm.mode = 20;
	tHomePrm.moveDir = -1;
	tHomePrm.indexDir = -1;
	tHomePrm.edge = 0;
	tHomePrm.velHigh = vel_high;
	tHomePrm.velLow = vel_low;
	tHomePrm.acc = 5;
	tHomePrm.dec = 5;
	tHomePrm.smoothTime = 1;
	tHomePrm.searchHomeDistance = 0;
	tHomePrm.searchIndexDistance = 0;
	tHomePrm.escapeStep = 0;
	tHomePrm.homeOffset = home_offset;
	rt = GT_GoHome(axisNum, &tHomePrm);

	step_home = true;
	//do {
	//	GT_GetHomeStatus(axisNum,&tHomeSts);
	//} while (tHomeSts.run);
	//GT_ZeroPos(axisNum);
	return true;
}

//设定点运动模式
void Axis::jogStop() {
	GT_Stop(1<<axisNum-1,1<<axisNum-1);

}


void Axis::jogIncrease() {

	// 将AXIS轴设为Jog模式
	GT_PrfJog(axisNum);
	// 读取Jog运动参数
	GT_GetJogPrm(axisNum, &jog);
	jog.acc = 0.0625;
	jog.dec = 0.0625;
	GT_SetJogPrm(axisNum, &jog);
	
	GT_SetVel(axisNum, vel_jog);
	GT_Update(1 << (axisNum - 1));

}

void Axis::jogDecrease() {

	// 将AXIS轴设为Jog模式
	GT_PrfJog(axisNum);
	// 读取Jog运动参数
	GT_GetJogPrm(axisNum, &jog);
	jog.acc = 0.0625;
	jog.dec = 0.0625;
	GT_SetJogPrm(axisNum, &jog);

	GT_SetVel(axisNum, -vel_jog);
	GT_Update(1 << (axisNum - 1));

}
void Axis::reset() {

	GT_ClrSts(axisNum);
}
void Axis::enableAxis() {

	if (GT_AxisOn(axisNum) == 0) enable = true;
}

void Axis::disableAxis() {

	if (GT_AxisOff(axisNum) == 0) enable = false;
}


bool Axis::MoveToPos(double position,double velocity) {
	rt = 0;
	pos = position;
	rt = GT_SetCaptureMode(axisNum, CAPTURE_INDEX);
	// 切换到点位运动模式
	rt = GT_PrfTrap(axisNum);
	// 读取点位模式运动参数
	rt = GT_GetTrapPrm(axisNum, &trapPrm);
	trapPrm.acc = 5;
	trapPrm.dec = 5;
	// 设置点位模式运动参数
	rt = GT_SetTrapPrm(axisNum, &trapPrm);
	// 设置点位模式目标速度，即回原点速度
	rt = GT_SetVel(axisNum, velocity);
	// 设置点位模式目标位置，即原点搜索距离
	rt = GT_SetPos(axisNum, position);
	// 启动运动
	rt = GT_Update(1 << (axisNum - 1));
	step_p2p = true;
	step_p2p_done = false;
	//do
	//{
	//	// 读取AXIS轴的状态
	//	GT_GetSts(axisNum, &status);
	//	// 读取AXIS轴的规划位置
	//	GT_GetPrfPos(axisNum, &prfPos);
	//} while (status & 0x400);	// 等待AXIS轴规划停止


	 return true;
}

void Axis::run() {
	if (step_home) {
	
		GT_GetHomeStatus(axisNum, &tHomeSts);
		
		if (!tHomeSts.run) {
			GT_ZeroPos(axisNum);
			step_home = false;
			in_home_pos = true;
		}
	}

	if (step_p2p) {
		// 读取AXIS轴的状态
		GT_GetSts(axisNum, &status);
		// 读取AXIS轴的规划位置
		GT_GetPrfPos(axisNum, &prfPos);

		if (!(status & 0x400)) {
			step_p2p = false;
			step_p2p_done = true;
			if (prfPos != pos) {
				error = true;
				errorDiscript = "Move to position failed.";
			}
		} 
	}

	// 读取规划位置
	rt = GT_GetPrfPos(axisNum, &prfPos);
	// 读取编码器位置
	rt = GT_GetEncPos(axisNum, &encPos);
	// 读取AXIS轴的状态
	GT_GetSts(axisNum, &status);
}