#include "LusterCameraClass.h"

LusterCameraClass::LusterCameraClass(QObject *parent)
	: QObject(parent)
{


}

LusterCameraClass::~LusterCameraClass()
{


}

void LusterCameraClass::initialize() {
	handle = NULL;
	m_pSaveImageBuf = NULL;
	m_nSaveImageBufSize = 0;
	memset(&(m_stImageInfo), 0, sizeof(MV_FRAME_OUT_INFO_EX));
	m_bStartGrabbing = false;
	OpenDevices();
}

void LusterCameraClass::singleGrab()
{

	int nRet = 0;
	if (m_bStartGrabbing) {

		m_bStartGrabbing = false;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		nRet = MV_CC_StopGrabbing(handle);

		if (MV_OK != nRet)
		{
			this->textEdit->append("Camera single grab stop grabbing fail!");
		}
	
	}
		MV_CC_StartGrabbing(handle);

		m_nTriggerMode = MV_TRIGGER_MODE_ON;
		 nRet = MV_CC_SetEnumValue(handle, "TriggerMode", m_nTriggerMode);
		if (MV_OK != nRet)
		{

			this->textEdit->append("Set Trigger mode fail!");
		}

		MV_CC_SetEnumValue(handle,"TriggerSource",MV_TRIGGER_SOURCE_SOFTWARE);
		MV_CC_SetCommandValue(handle, "TriggerSoftware");
		grabOnce();
		MV_CC_StopGrabbing(handle);

}


void LusterCameraClass::grabOnce() {

	int nRet = MV_OK;
	MV_FRAME_OUT stImageInfo = { 0 };
	MV_DISPLAY_FRAME_INFO stDisplayInfo = { 0 };

	nRet = MV_CC_GetImageBuffer(handle, &stImageInfo, 1000);
	if (nRet == MV_OK)
	{
		if (mtx->try_lock())
		{
		   emit sendGrabResultSigal(stImageInfo.pBufAddr, stImageInfo.stFrameInfo.nWidth,stImageInfo.stFrameInfo.nHeight, cameraID);


			mtx->unlock();
		}

		nRet = MV_CC_FreeImageBuffer(handle, &stImageInfo);
		if (nRet != MV_OK)
		{
			this->textEdit->append("Free Image Buffer fail!");
		}
	}
	else
	{
		this->textEdit->append("Get Image fail!");
	}

}
void LusterCameraClass::continuousGrab() {

	if (m_bStartGrabbing) return;

	m_nTriggerMode = MV_TRIGGER_MODE_OFF;
	int nRet = MV_CC_SetEnumValue(handle, "TriggerMode", m_nTriggerMode);
	if (MV_OK != nRet)
	{
		this->textEdit->append("Set Trigger mode fail!");
	}


		nRet = MV_CC_StartGrabbing(handle);

		if (MV_OK != nRet)
		{
			this->textEdit->append("continuous start grabbing fail!");
		}
		//m_hGrabThread[cameraNumChosed] = std::thread(&LusterCameraClass::continuousGrabThread, this);
		m_hGrabThread = std::thread(&LusterCameraClass::continuousGrabThread, this);

		m_bStartGrabbing= true;
		m_hGrabThread.detach();
		//this->continuousGrabThread(0);
	
}
void LusterCameraClass::continuousGrabThread() {


	while (1)
	{

		grabOnce();
		if (m_bStartGrabbing == false)
		{
			break;
		}
	}

	return;

}
void LusterCameraClass::OpenDevices()
{
	if (TRUE == m_bOpenDevice)
	{


		return;
	}

			// ch:选择设备并创建句柄 | en:Select device and create handle
			int nRet = MV_CC_CreateHandle(&handle, deviceInfo);
			if (MV_OK != nRet)
			{
				this->textEdit->append("Create Handle fail!");
			}

			// ch:打开设备 | en:Open device
			nRet = MV_CC_OpenDevice(handle);
			if (MV_OK != nRet)
				this->textEdit->append("Open Device fail!");
			else
				m_bOpenDevice = true;

}
