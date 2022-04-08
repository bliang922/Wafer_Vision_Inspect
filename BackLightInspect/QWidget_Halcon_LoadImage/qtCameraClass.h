#pragma once
// Include files to use the pylon API.
//#include <pylon/PylonIncludes.h>
#include "HalconCpp.h"
#include <thread>
#include <QObject>
#ifdef PYLON_WIN_BUILD
#    include <pylon/PylonGUI.h>
#endif

// Namespace for using pylon objects.
using namespace Pylon;
using namespace HalconCpp;

// Namespace for using cout.
using namespace std;

class qtCameraClass :public QObject, public CImageEventHandler
{
	Q_OBJECT

public:
	qtCameraClass(QObject *parent);
	~qtCameraClass();

	std::thread continousGrabThread;
	void   initialize();
	void   singleGrab();
	void OnImageGrabbed(CInstantCamera& camera, const CGrabResultPtr& ptrGrabResult);

	void   continuousGrab();
	CInstantCamera *cmr;
	CGrabResultPtr ptrGrabResult;

signals:
	void sendGrabResultSigal(CGrabResultPtr CGrabResultPtr);

};
