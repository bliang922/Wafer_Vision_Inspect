#pragma once

#include <QObject>
#include <thread>
#include "HalconCpp.h"
#include <QtWidgets>
#include <mutex>
#include "MvCameraControl.h"


class LusterCameraClass : public QObject
{
	Q_OBJECT

public:
	LusterCameraClass(QObject *parent);

	~LusterCameraClass();
	QTextEdit *textEdit;
	std::mutex *mtx;

	int cameraID;
	void* handle;

	unsigned int    m_nValidCamNum;
	BOOL            m_bOpenDevice;
	BOOL            m_bStartGrabbing;
	int             m_nTriggerMode;
	int             m_nTriggerSource;
	std::thread     m_hGrabThread;
	MV_CC_DEVICE_INFO* deviceInfo;
	CRITICAL_SECTION        m_hSaveImageMux;
	unsigned char*          m_pSaveImageBuf;
	unsigned int            m_nSaveImageBufSize;
	MV_FRAME_OUT_INFO_EX    m_stImageInfo;

	int m_nCurCameraIndex;

	void   initialize();

	void   singleGrab();
	void continuousGrabThread();
	//void OnImageGrabbed(CInstantCamera& camera, const CGrabResultPtr& ptrGrabResult);

	void   continuousGrab();
	//CInstantCamera *cmr;
	uint8_t * ptrGrabResult;
	void OpenDevices();
	void grabOnce();
signals:
	void sendGrabResultSigal(uint8_t * imgBufferPtr,int imgWidth,int imgHeight,int cameraNum);
};
