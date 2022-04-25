#include "TeleDyneCamera.h"

TeleDyneCamera *classPointer = NULL;
void AcqCallback(SapXferCallbackInfo *pInfo)
{
	SapView *pView = (SapView *)pInfo->GetContext();

	// Resfresh view
	pView->Show();
}

TeleDyneCamera::TeleDyneCamera(QObject *parent)
	: QObject(parent)
{
}

TeleDyneCamera::~TeleDyneCamera()
{
}

bool TeleDyneCamera::initialize() {
	classPointer = this;

	acqServerName = "Xtium-CL_MX4_1";
	acqDeviceNumber = 0;
	configFilename = ".\\T_LA_CM_08K08A_00_R_FreeRun_Default.ccf";
	//"C:\\Program Files\\Teledyne DALSA\\Sapera\\CamFiles\\User\\T_LA_CM_08K08A_00_R_FreeRun_Default.ccf"
	SapLocation loc(acqServerName, acqDeviceNumber);

	if (SapManager::GetResourceCount(acqServerName, SapManager::ResourceAcq) > 0)
	{
		Acq = new SapAcquisition(loc, configFilename);
		Buffers = new SapBuffer(1, Acq);
		View = new SapView(Buffers, SapHwndAutomatic);
		Xfer = new SapAcqToBuf(Acq, Buffers, AcqCallback, View);

		// Create acquisition object
		if (Acq && !*Acq && !Acq->Create())
			acquisitionCreated = FALSE;
	}


	//get the SapAcqDevice (camera)
	acqServerName = "CameraLink_1";
	SapLocation loc2(acqServerName, acqDeviceNumber);
	AcqDevice = new SapAcqDevice(loc2, FALSE);
	Feature = new SapFeature(acqServerName);
	status = Feature->Create();

	//create SapAcqDevice
	if (AcqDevice && !*AcqDevice && !AcqDevice->Create())
		acqDeviceCreated = FALSE;

	//if any of the frame grabber or camera failed to initialize, end program
	if (!acquisitionCreated || !acqDeviceCreated) {
		close();
		return false;
	} 
		
	//check to see if this is a DFNC camera. If it is not, end program
	//Program checks for both current and legacy naming
	char modelName[64];
	AcqDevice->IsFeatureAvailable("DeviceModelName", &status);
	if (status)
	{
		AcqDevice->GetFeatureValue("DeviceModelName", modelName, sizeof(modelName));
		if (strstr(modelName, "Genie") != 0)
		{
			isNotSupported = TRUE;
		}
	}
	else
	{
		isNotSupported = TRUE;
	}
	if (isNotSupported)
	{
		printf("Current camera model is not supported.\n");
		close();
		return false;
	}

	// Create buffer object
	if (Buffers && !*Buffers && !Buffers->Create()) {
		close();
		return false;
	}  

	// Create transfer object
	if (Xfer && !*Xfer && !Xfer->Create()) {
		close();
		return false;
	}

	// Create view object
	if (View && !*View && !View->Create()) {
		close();
		return false;
	}


}

void TeleDyneCamera::startGrab() {

	// Start continous grab
	Xfer->Grab();
}

void TeleDyneCamera::stopGrab() {

	// Stop grab
	Xfer->Freeze();
	if (!Xfer->Wait(5000))
	{
		printf("Grab could not stop properly.\n");
		Xfer->Abort();
	}
}

bool TeleDyneCamera::close() {
	// Destroy view object
	if (View && *View && !View->Destroy()) return FALSE;

	// Destroy transfer object
	if (Xfer && *Xfer && !Xfer->Destroy()) return FALSE;

	// Destroy buffer object
	if (Buffers && *Buffers && !Buffers->Destroy()) return FALSE;

	// Destroy acquisition object
	if (Acq && *Acq && !Acq->Destroy()) return FALSE;

	// Destroy feature object
	if (Feature && *Feature && !Feature->Destroy()) return FALSE;

	// Destroy acquisition object
	if (AcqDevice && *AcqDevice && !AcqDevice->Destroy()) return FALSE;


	// Delete all objects
	if (View)		delete View;
	if (Xfer)		delete Xfer;
	if (Buffers)	delete Buffers;
	if (Acq)		delete Acq;
	if (Feature)		delete Feature;
	if (AcqDevice)	delete AcqDevice;
	return 0;

}
