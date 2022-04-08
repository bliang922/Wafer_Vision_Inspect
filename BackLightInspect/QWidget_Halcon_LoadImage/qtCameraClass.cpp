#include "qtCameraClass.h"

qtCameraClass::qtCameraClass(QObject *parent)
	: QObject(parent)
{
//	initialize();
}

qtCameraClass::~qtCameraClass()
{
	PylonTerminate();

}

void qtCameraClass::initialize() {

	//Before using any pylon methods, the pylon runtime must be initialized.
	PylonInitialize();

	//Get the transport layer factory.
	CTlFactory& tlFactory = CTlFactory::GetInstance();

	//Create an instant camera object with the camera device found first.
	cmr = new CInstantCamera(tlFactory.CreateFirstDevice());
	cmr->MaxNumBuffer = 5;

	//GenApi::INodeMap &cameraNodeMap = cmr->GetNodeMap();
	//const GenApi::CBooleanPtr frameRate = cameraNodeMap.GetNode("AcquisitionFrameRateEnable");
	//frameRate->SetValue(TRUE);
	//const GenApi::CFloatPtr frameRateABS = cameraNodeMap.GetNode("AcquisitionFrameRateAbs");
	//frameRateABS->SetValue(5);
	// Register the standard configuration event handler for enabling software triggering.
	// The software trigger configuration handler replaces the default configuration
	// as all currently registered configuration handlers are removed by setting the registration mode to RegistrationMode_ReplaceAll.
	//cmr->RegisterConfiguration(new CSoftwareTriggerConfiguration, RegistrationMode_ReplaceAll, Cleanup_Delete);
	cmr->RegisterImageEventHandler(this, RegistrationMode_Append, Cleanup_Delete);
	cmr->Open();
}

void qtCameraClass::singleGrab() {

	if(cmr->IsGrabbing())
		cmr->StopGrabbing();

	//Start the grabbing of c_countOfImagesToGrab images.
	cmr->StartGrabbing(1);

	cmr->RetrieveResult(3000, ptrGrabResult, TimeoutHandling_ThrowException);
	emit sendGrabResultSigal(ptrGrabResult);
}

void qtCameraClass::OnImageGrabbed(CInstantCamera& cam, const CGrabResultPtr& ptrGrabResult)
{
//	std::this_thread::sleep_for(100ms);

	string name = cam.GetDeviceInfo().GetSerialNumber();
	emit sendGrabResultSigal(ptrGrabResult);
}

void qtCameraClass::continuousGrab() {

	//Start the grabbing of c_countOfImagesToGrab images.
	if (cmr->IsGrabbing()) {
		cmr->StopGrabbing();
	}
		cmr->StartGrabbing(GrabStrategy_OneByOne, GrabLoop_ProvidedByInstantCamera);
	

	//cmr->Open();
	//while (1)
	//{
	//	if (cmr->WaitForFrameTriggerReady(500, TimeoutHandling_ThrowException))
	//	{
	//		cmr->ExecuteSoftwareTrigger();
	//	}

	//	//cmr->RetrieveResult(5000, ptrGrabResult, TimeoutHandling_Return);
	//	//if (ptrGrabResult->GrabSucceeded()) {
	//	//	const uint8_t *pImageBuffer = (uint8_t *)ptrGrabResult->GetBuffer();//获取图像在内存中的地址
	//	//	//qDebug() << "Gray value of first pixel: " << (uint32_t)pImageBuffer[0];


	//	//}

	////}
	//}
}

