#include "GTS_800_ACC2.h"

bool GTS_800_ACC2::initialize() {
	
	// 如果指令执行返回值为非0，说明指令执行错误
	rt = 0;
	rt = GT_Open();
	if (rt) return false;
	rt= GT_Reset();
	if (rt) return false;
	char  configFilePath[] = ".\\config.cfg";

	//加载固高运动控制卡伺服轴配置文件
	rt = GT_LoadConfig(configFilePath);
	if (rt) return false;
	rt = GT_ClrSts(1,2);//使loadConfig指令生效

	// 轴伺服使能
	rt = GT_AxisOn(AXIS1_LOAD);
	if (rt) return false;
	rt = GT_AxisOn(AXIS2_ROTATE);
	if (rt) return false;

	homePosition(AXIS1_LOAD);
	homePosition(AXIS2_ROTATE);

	if (rt) return false;
	else return true;
}

bool GTS_800_ACC2::homePosition(short axis) {
	// 启动Home捕获
	rt = GT_SetCaptureMode(axis, CAPTURE_HOME);
	// 切换到点位运动模式
	rt = GT_PrfTrap(axis);
	// 读取点位模式运动参数
	rt = GT_GetTrapPrm(axis, &trapPrm);
	trapPrm.acc = 0.25;
	trapPrm.dec = 0.25;
	// 设置点位模式运动参数
	rt = GT_SetTrapPrm(axis, &trapPrm);
	// 设置点位模式目标速度，即回原点速度
	rt = GT_SetVel(axis, 10);
	// 设置点位模式目标位置，即原点搜索距离
	rt = GT_SetPos(axis, SEARCH_HOME);
	// 启动运动
	rt = GT_Update(1 << (axis - 1));

	do
	{
		// 读取轴状态
		GT_GetSts(axis, &status);
		// 读取捕获状态
		GT_GetCaptureStatus(axis, &capture, &pos);
		// 读取规划位置
		GT_GetPrfPos(axis, &prfPos);
		// 读取编码器位置
		GT_GetEncPos(axis, &encPos);
		// 如果运动停止，返回出错信息
		if (0 == (status & 0x400))
		{
			error = true;
			errorDiscript = "Homing failed.";
			return false;
		}
		// 等待捕获触发
	} while (0 == capture);


	// 运动到"捕获位置+偏移量"
	rt = GT_SetPos(axis, pos+HOME_OFFSET);
	// 在运动状态下更新目标位置
	rt = GT_Update(1 << (axis - 1));

	do
	{
		// 读取轴状态
		GT_GetSts(axis, &status);
		// 读取规划位置
		GT_GetPrfPos(axis, &prfPos);
		// 读取编码器位置
		GT_GetEncPos(axis, &encPos);
		// 等待运动停止
	} while (status & 0x400);
	// 检查是否到达"Home捕获位置+偏移量"
	if (prfPos != pos + HOME_OFFSET)
	{
		error = true;
		errorDiscript = "Axis move to position failed.";
		return false;
	}
	// 延时一段时间，等待电机停稳
	std::this_thread::sleep_for(std::chrono::milliseconds(200));

	// 位置清零
	rt = GT_ZeroPos(axis);
	// 读取规划位置
	rt = GT_GetPrfPos(axis, &prfPos);
	// 读取编码器位置
	rt = GT_GetEncPos(axis, &encPos);
	// 读取axis规划位置
	rt = GT_GetAxisPrfPos(axis, &axisPrfPos);
	// 读取axis编码器位置
	rt = GT_GetAxisEncPos(axis, &axisEncPos);
	return true;

}

void GTS_800_ACC2::close() {
	// 伺服关闭

	GT_AxisOff(AXIS1_LOAD);
	GT_AxisOff(AXIS2_ROTATE);

}


bool GTS_800_ACC2::MoveToPos(short axis,double position,double velocity) {
	rt = 0;
	rt = GT_SetCaptureMode(axis, CAPTURE_INDEX);
	// 切换到点位运动模式
	rt = GT_PrfTrap(axis);
	// 读取点位模式运动参数
	rt = GT_GetTrapPrm(axis, &trapPrm);
	trapPrm.acc = 0.25;
	trapPrm.dec = 0.25;
	// 设置点位模式运动参数
	rt = GT_SetTrapPrm(axis, &trapPrm);
	// 设置点位模式目标速度，即回原点速度
	rt = GT_SetVel(axis, velocity);
	// 设置点位模式目标位置，即原点搜索距离
	rt = GT_SetPos(axis, position);
	// 启动运动
	rt = GT_Update(1 << (axis - 1));

	do
	{
		// 读取AXIS轴的状态
		GT_GetSts(axis, &status);
		// 读取AXIS轴的规划位置
		GT_GetPrfPos(axis, &prfPos);
	} while (status & 0x400);	// 等待AXIS轴规划停止

	if (prfPos != position) {
		error = true;
		errorDiscript = "Move to position failed.";
		return false;
	}
	else return true;
}