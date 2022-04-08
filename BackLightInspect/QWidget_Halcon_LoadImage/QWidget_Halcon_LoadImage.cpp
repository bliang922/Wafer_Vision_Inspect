#include "QWidget_Halcon_LoadImage.h"
#include <QtWidgets>
#include<thread>


QWidget_Halcon_LoadImage::QWidget_Halcon_LoadImage(QWidget *parent)
    : QMainWindow(parent)
{


    ui.setupUi(this);
	//qRegisterMetaType<CInstantCamera>("CInstantCamera");


/*******************************************Image Grab Initialize*******************************************************************/
	//Basler Camera
	//qRegisterMetaType<CGrabResultPtr>("CGrabResultPtr");
	memset(&m_stDevList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
	int nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &m_stDevList);

	for (int i = 0;i < DEVICE_NUM;i++) {
		camera[i] = new LusterCameraClass(NULL);
		camera[i]->textEdit = ui.textEdit_status;
		camera[i]->mtx = &this->mtx_camera;
		camera[i]->cameraID = i;
		camera[i]->deviceInfo = m_stDevList.pDeviceInfo[i];
		camera[i]->initialize();
		connect(camera[i], &LusterCameraClass::sendGrabResultSigal, this, &QWidget_Halcon_LoadImage::imageGrabbed);

	}

	if (MV_OK != nRet || m_stDevList.nDeviceNum == 0)
	{
		ui.textEdit_status->append("Find no camera device!");
	}else
	ui.textEdit_status->append(QString("Find camera devices! ") + m_stDevList.nDeviceNum);

	//camera
	connect(ui.btn_loadImage, SIGNAL(clicked()), this, SLOT(btn_loadImage_clicked()));
	connect(ui.btn_loadcontinuImage, SIGNAL(clicked()), this, SLOT(btn_loadcontinuImage_clicked()));
//	connect(ui.actionZoomIn, SIGNAL(triggered()), this, SLOT(zoomIn_clicked()));
//	connect(ui.actionZoomOut, SIGNAL(triggered()), this, SLOT(zoomOut_clicked()));
//	connect(ui.actionNormalSize, SIGNAL(triggered()), this, SLOT(normalSize_clicked()));
	connect(ui.exitButton, SIGNAL(clicked()), this, SLOT(exitButton_clicked()));
	connect(ui.btn_saveImage, SIGNAL(clicked()), this, SLOT(saveImageButton_clicked()));

//	connect(camera,SIGNAL(sendGrabResultSigal(CGrabResultPtr)), this, SLOT(imageGrabbed(CGrabResultPtr)));


	connect(ui.checkBox, SIGNAL(clicked(bool)), this, SLOT(checkBox_clicked()));
	connect(ui.checkBox_2, SIGNAL(clicked(bool)), this, SLOT(checkBox_clicked()));
	connect(ui.checkBox_3, SIGNAL(clicked(bool)), this, SLOT(checkBox_clicked()));


	//ui.label->setFixedHeight(531);
	//ui.label->setFixedWidth(591);
	imageLabel[0] = ui.label;
	imageLabel[1] = ui.label_2;
	imageLabel[2] = ui.label_3;

	for (int i = 0; i < DEVICE_NUM; i++) {
		windowID[i] = imageLabel[i]->winId();
	//	windowID[0] = ui.label->winId();
		OpenWindow(0, 0, imageLabel[i]->width(), imageLabel[i]->height(), windowID[i], "visible", "", &windowHandle[i]);

		SetLineWidth(windowHandle[i], 2);
		SetColor(windowHandle[i], "red");
		int height = imageLabel[i]->height();
		int width = imageLabel[i]->width();
		//SetPart(windowHandle[0], 0, 0, height, width);

	}
if(camera[0]->m_bOpenDevice)
	ui.Indicator_Camera->setStyleSheet("background-color:rgb(0,255,127)");
else ui.Indicator_Camera->setStyleSheet("background-color:rgb(128,138,135)");

if (camera[1]->m_bOpenDevice)
ui.Indicator_Camera2->setStyleSheet("background-color:rgb(0,255,127)");
else ui.Indicator_Camera2->setStyleSheet("background-color:rgb(128,138,135)");

if (camera[2]->m_bOpenDevice)
ui.Indicator_Camera3->setStyleSheet("background-color:rgb(0,255,127)");
else ui.Indicator_Camera3->setStyleSheet("background-color:rgb(128,138,135)");

/*******************************************ModbusTCP communication Initialize*******************************************************************/
	client = new ClientClass(NULL);
	client->mtx = &this->mtx_modbus;
	client->textEdit = ui.textEdit_status;

	connect(ui.sendButton,SIGNAL(clicked()), this, SLOT(btn_send_clicked()));
	connect(client, &ClientClass::valueChanged, this, &QWidget_Halcon_LoadImage::valueChanged);
	connect(client, &ClientClass::plcDataUpdate, this, &QWidget_Halcon_LoadImage::plcDataUpdate);
	//show table grid 
	ui.table_IO->setShowGrid(true);
	
	//set table grid line to DashLine or DotLine
	//ui.table_IO->setGridStyle(Qt::DashLine);
	//ui.table_IO->setSortingEnabled(true);
	model_PLC_IO = new QStandardItemModel();
	QStringList labels = QObject::trUtf8("PLC_tag,Address,Value").simplified().split(",");
	model_PLC_IO->setHorizontalHeaderLabels(labels);

	client->initialize();
	client->lauchCommThread();
	ui.table_IO->setModel(model_PLC_IO);
	ui.table_IO->show();

	if (client->modbusConnected)
		ui.Indicator_Comm->setStyleSheet("background-color:rgb(0,255,127)");
	else ui.Indicator_Comm->setStyleSheet("background-color:rgb(128,138,135)");

	model_alarms = new QStandardItemModel();
	QStringList labels2 = QObject::trUtf8("Time,Device,Code,Discript").simplified().split(",");
	model_alarms->setHorizontalHeaderLabels(labels2);
	ui.table_alarm->setModel(model_alarms);
	ui.table_alarm->setShowGrid(true);

	ui.table_alarm->show();

/*******************************************SQLite Initialize*******************************************************************/
	//show table grid 
	ui.table_static1->setShowGrid(true);
	//set table grid line to DashLine or DotLine
	ui.table_static1->setGridStyle(Qt::DashLine);
	ui.table_static1->setSortingEnabled(true);
	model_sql_data = new QStandardItemModel();
	QStringList labels_2 = QObject::trUtf8("TIME,TOTAL,OK_TOTAL,NG_TOTAL,OK_RATE,SHIFT").simplified().split(",");
	model_sql_data->setHorizontalHeaderLabels(labels_2);

	ui.table_static1->setModel(model_sql_data);
	ui.table_static1->setShowGrid(true);
	ui.table_static1->show();
	
	sql = new SQLiteClass(NULL);
	sql->textEdit = ui.textEdit_status;
	sql->mtx = &this->mtx_sql;

	connect(sql, &SQLiteClass::sendQueryResult, this, &QWidget_Halcon_LoadImage::query_returned);

	sql->initialize();

	if (sql->sql_open)
		ui.Indicator_Database->setStyleSheet("background-color:rgb(0,255,127)");
	else ui.Indicator_Database->setStyleSheet("background-color:rgb(128,138,135)");

/*******************************************IOC0640 IO Module Initialize*******************************************************************/
	connect(ioc0640, &Controller_IOC0640::loadPartDone, this, &QWidget_Halcon_LoadImage::valueChanged);

	ioc0640.mtx = &this->mtx_ioc0640;
	ioc0640.textEdit = ui.textEdit_status;
	ioc0640.pc_done = true;
}





/*******************************************Image Grab*******************************************************************/
void QWidget_Halcon_LoadImage::exitButton_clicked() {
	
	QApplication::quit();
}

void QWidget_Halcon_LoadImage::saveImageButton_clicked() {

	for (int i = 0;i < DEVICE_NUM;i++) {
		if (cameraChecked[i] == 2)
			//WriteImage(image[i], "bmp", 0, "D:\\Projects\\BackLightInspect\\QWidget_Halcon_LoadImage\\pic\\pic1.bmp" );
		WriteImage(image[i], "bmp", 0, "D:\\pic1.bmp");

	}
}

void QWidget_Halcon_LoadImage::btn_loadcontinuImage_clicked() {
	
	for (int i = 0;i < DEVICE_NUM;i++) {
		if (cameraChecked[i] == 2)
			camera[i]->continuousGrab();
	}
}

void QWidget_Halcon_LoadImage::btn_loadImage_clicked()
{
	for (int i = 0;i < DEVICE_NUM;i++) {
		if(cameraChecked[i]==2)
		camera[i]->singleGrab();
	}
}


void QWidget_Halcon_LoadImage::checkBox_clicked() {

	cameraChecked[0] = ui.checkBox->checkState();
	cameraChecked[1] = ui.checkBox_2->checkState();
	cameraChecked[2] = ui.checkBox_3->checkState();

}

void QWidget_Halcon_LoadImage::imageGrabbed(uint8_t * imgBufferPtr, int imgWidth, int imgHeight,int cameraNum) {

	//Basler Camera
	/*//直接用halcon算子转化为HObject 格式	(此算子只适用单个通道)
	 const uint8_t *pImageBuffer = (uint8_t *)ptrGrabResult->GetBuffer();
	GenImage1(&image, "byte", (Hlong)ptrGrabResult->GetWidth(), (Hlong)ptrGrabResult->GetHeight(), (Hlong)pImageBuffer);
	GetImageSize(image, &imgWidth, &imgHeight);*/

	//Luster Camera



			/*GenImage1(&image[cameraNum], "byte", (Hlong)imgWidth, (Hlong)imgHeight, (Hlong)imgBufferPtr);
			WriteImage(image[0], 'bmp', 0, "D:\Projects\BackLightInspect\QWidget_Halcon_LoadImage\pic\1.bmp");*/

			GenImage1(&image[cameraNum], "byte", (Hlong)imgWidth, (Hlong)imgHeight, (Hlong)imgBufferPtr);
			//WriteImage(img, 'tiff', 0, "D://1.tif");
			//WriteImage(image[cameraNum], "bmp", 0, "D:\\1.bmp");
			SetPart(windowHandle[cameraNum], 0, 0, imgHeight, imgWidth);

			if (image[cameraNum].IsInitialized()) {
				DispObj(image[cameraNum], windowHandle[cameraNum]);
			}

}
void QWidget_Halcon_LoadImage::measure() {


}




/*******************************************ModbusTCP communication*******************************************************************/
void QWidget_Halcon_LoadImage::valueChanged() {

	ui.textEdit_status->append("PLC data at address 0 has changed");
}

void QWidget_Halcon_LoadImage::plcDataUpdate() {

	QStandardItem *item = 0;
	long int * pointer;
	pointer = (long *)client->recvbuf;
	int index = 0;

	for (int i = 0; i < 25; i++) {

		index = i * 2;
		item = new QStandardItem(QString::number(index));
		model_PLC_IO->setItem(index, 0, item);

		item = new QStandardItem(QString::number(index));
		model_PLC_IO->setItem(index, 1, item);

		//long temp = std::stol((char *)pointer, nullptr, 10);
		item = new QStandardItem(QString::number(*pointer));
		model_PLC_IO->setItem(index, 2, item);
		pointer++;
	}
	ui.table_IO->update();
}

void QWidget_Halcon_LoadImage::btn_send_clicked() {
	if (ui.lineEdit->text().length() != 0) {
		if (client->mtx->try_lock()) {
			//strcpy((char *) client->sendbuf,  ui.lineEdit->text().toLocal8Bit().data());
			client->sendbuf[0] = ui.lineEdit->text().toInt();

			client->mtx->unlock();
		}
	}

}



/*******************************************SQLite*******************************************************************/
void QWidget_Halcon_LoadImage::query_returned(int argc, char **argv, char **azColName) {

	QStandardItem *item = 0;

	//int i;
//for (i = 0; i < argc; i++) {
//	printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//}
//printf("\n");


	for (int i = 0; i < argc; i++) {

		item = new QStandardItem(QString::QString(argv[i]));
		model_sql_data->setItem(sql->resultCount, i, item);
	}
	sql->resultCount++;
	ui.table_static1->update();
}


