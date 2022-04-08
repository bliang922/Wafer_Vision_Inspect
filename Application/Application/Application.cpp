#include "Application.h"

Application::Application(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	/*******************************************Image process Initialize*******************************************************************/
	//Basler Camera
	//qRegisterMetaType<CGrabResultPtr>("CGrabResultPtr");
	memset(&m_stDevList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
	int nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &m_stDevList);

	if (MV_OK != nRet || m_stDevList.nDeviceNum == 0)
	{
		ui.textEdit_status->append("Find no camera device!");
	}

	else {
		ui.textEdit_status->append(QString("Find ") + QString::number(m_stDevList.nDeviceNum) + " camera devices!");

		for (int i = 0; i < DEVICE_NUM; i++) {
			//camera initialize
			camera[i] = new LusterCameraClass(NULL);
			camera[i]->textEdit = ui.textEdit_status;
			camera[i]->mtx = &this->mtx_camera;
			camera[i]->cameraID = i;
			camera[i]->deviceInfo = m_stDevList.pDeviceInfo[i];
			camera[i]->initialize();
			connect(camera[i], &LusterCameraClass::sendGrabResultSigal, this, &QWidget_Halcon_LoadImage::imageGrabbed);

			//algorithm initialize
			algorithm[i] = new Algorithm(NULL);
			algorithm[i]->textEdit = ui.textEdit_status;
			algorithm[i]->mtx = &this->mtx_camera;
			algorithm[i]->cameraNum = i;
			connect(algorithm[i], &Algorithm::processImageDone, this, &QWidget_Halcon_LoadImage::showImage);

		}

	}




	//connect button commands to slots
	connect(ui.btn_loadImage, SIGNAL(clicked()), this, SLOT(btn_loadImage_clicked()));
	connect(ui.btn_loadcontinuImage, SIGNAL(clicked()), this, SLOT(btn_loadcontinuImage_clicked()));
	//	connect(ui.actionZoomIn, SIGNAL(triggered()), this, SLOT(zoomIn_clicked()));
	//	connect(ui.actionZoomOut, SIGNAL(triggered()), this, SLOT(zoomOut_clicked()));
	//	connect(ui.actionNormalSize, SIGNAL(triggered()), this, SLOT(normalSize_clicked()));
	connect(ui.exitButton, SIGNAL(clicked()), this, SLOT(exitButton_clicked()));
	connect(ui.btn_saveImage, SIGNAL(clicked()), this, SLOT(saveImageButton_clicked()));
	connect(ui.btn_reset, SIGNAL(clicked()), this, SLOT(resetButton_clicked()));
	connect(ui.btn_light, SIGNAL(clicked()), this, SLOT(lightButton_clicked()));
	connect(ui.btn_LED1, SIGNAL(clicked()), this, SLOT(LED1Button_clicked()));
	connect(ui.btn_LED2, SIGNAL(clicked()), this, SLOT(LED2Button_clicked()));
	connect(ui.btn_rotate, SIGNAL(clicked()), this, SLOT(rotateButton_clicked()));

	//	connect(camera,SIGNAL(sendGrabResultSigal(CGrabResultPtr)), this, SLOT(imageGrabbed(CGrabResultPtr)));


		//connect check box to slots, initialize check box to checked
	connect(ui.checkBox, SIGNAL(clicked(bool)), this, SLOT(checkBox_clicked()));
	connect(ui.checkBox_2, SIGNAL(clicked(bool)), this, SLOT(checkBox_clicked()));
	connect(ui.checkBox_3, SIGNAL(clicked(bool)), this, SLOT(checkBox_clicked()));
	ui.checkBox->setCheckState(Checked), cameraChecked[0] = 2;
	ui.checkBox_2->setCheckState(Checked), cameraChecked[1] = 2;
	ui.checkBox_3->setCheckState(Checked), cameraChecked[2] = 2;


	//ui.label->setFixedHeight(531);
	//ui.label->setFixedWidth(591);
	imageLabel[0] = ui.label;
	imageLabel[1] = ui.label_2;
	imageLabel[2] = ui.label_3;

	//create window handles
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

	//set HMI camera status icon color
	if (camera[0]->m_bOpenDevice)   ui.Indicator_Camera->setStyleSheet("background-color:rgb(0,255,127)");
	else ui.Indicator_Camera->setStyleSheet("background-color:rgb(128,138,135)");

	if (camera[1]->m_bOpenDevice)  ui.Indicator_Camera2->setStyleSheet("background-color:rgb(0,255,127)");
	else ui.Indicator_Camera2->setStyleSheet("background-color:rgb(128,138,135)");

	if (camera[2]->m_bOpenDevice)  ui.Indicator_Camera3->setStyleSheet("background-color:rgb(0,255,127)");
	else ui.Indicator_Camera3->setStyleSheet("background-color:rgb(128,138,135)");



	/*******************************************ModbusTCP communication Initialize*******************************************************************/
	client = new ClientClass(NULL);
	client->mtx = &this->mtx_modbus;
	client->textEdit = ui.textEdit_status;

	connect(ui.sendButton, SIGNAL(clicked()), this, SLOT(btn_send_clicked()));
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

	//client->initialize();
	//client->lauchCommThread();
	ui.table_IO->setModel(model_PLC_IO);
	ui.table_IO->show();

	if (client->modbusConnected)  ui.Indicator_Comm->setStyleSheet("background-color:rgb(0,255,127)");
	else ui.Indicator_Comm->setStyleSheet("background-color:rgb(128,138,135)");

	model_alarms = new QStandardItemModel();
	QStringList labels2 = QObject::trUtf8("Time,Device,Discript").simplified().split(",");
	model_alarms->setHorizontalHeaderLabels(labels2);
	ui.table_alarm->setModel(model_alarms);
	ui.table_alarm->setShowGrid(true);

	ui.table_alarm->show();

	/*******************************************SQLite Initialize*******************************************************************/
		////show table grid 
		//ui.table_static1->setShowGrid(true);
		////set table grid line to DashLine or DotLine
		//ui.table_static1->setGridStyle(Qt::DashLine);
		//ui.table_static1->setSortingEnabled(true);
		//model_sql_data = new QStandardItemModel();
		//QStringList labels_2 = QObject::trUtf8("TIME,TOTAL,OK_TOTAL,NG_TOTAL,OK_RATE,SHIFT").simplified().split(",");
		//model_sql_data->setHorizontalHeaderLabels(labels_2);

		//ui.table_static1->setModel(model_sql_data);
		//ui.table_static1->setShowGrid(true);
		//ui.table_static1->show();

	ui.table_statistic->setModel(&product_stat.model_productData);
	sql = new SQLiteClass(NULL);
	sql->textEdit = ui.textEdit_status;
	sql->mtx = &this->mtx_sql;

	connect(sql, &SQLiteClass::sendQueryResult, this, &QWidget_Halcon_LoadImage::query_returned);

	sql->initialize();

	if (sql->sql_open)
		ui.Indicator_Database->setStyleSheet("background-color:rgb(0,255,127)");
	else ui.Indicator_Database->setStyleSheet("background-color:rgb(128,138,135)");


	//show table grid 
	ui.table_statistic->setShowGrid(true);
	//set table grid line to DashLine or DotLine
	ui.table_statistic->setGridStyle(Qt::DashLine);
	//ui.table_statistic->setSortingEnabled(true);
	model_sql_data = new QStandardItemModel();
	QStringList labels_2 = QObject::trUtf8("TIME,TOTAL,OK_TOTAL,NG_TOTAL,OK_RATE,SHIFT").simplified().split(",");
	model_sql_data->setHorizontalHeaderLabels(labels_2);

	ui.table_statistic->setModel(&product_stat.model_productData);
	ui.table_statistic->setShowGrid(true);
	ui.table_statistic->show();

	/*******************************************IOC0640 IO Module Initialize*******************************************************************/
	ioc0640 = new Controller_IOC0640(NULL);
	connect(ioc0640, &Controller_IOC0640::loadPartDone, this, &QWidget_Halcon_LoadImage::measure);
	connect(ioc0640, &Controller_IOC0640::raiseAlarm, this, &QWidget_Halcon_LoadImage::showAlarm);

	ioc0640->mtx = &this->mtx_ioc0640;
	ioc0640->textEdit = ui.textEdit_status;
	ioc0640->pc_done = true;

	ioc0640->initialize();
	ioc0640->lauchControllerThread();
}





/*******************************************Image *******************************************************************/
void Application::exitButton_clicked() {

	QApplication::quit();
}

void Application::resetButton_clicked() {

	ioc0640->solenoid_rotateStation->cmdReset = true;

	//change the alarm texts back to normal
	for (int i = 0; i < model_alarms->rowCount(); i++) {
		for (int j = 0; j < model_alarms->columnCount(); j++) {
			if (model_alarms->item(i, j)->foreground().color() == red)
				model_alarms->item(i, j)->setForeground(black);
		}

	}
}

void Application::saveImageButton_clicked() {

	for (int i = 0; i < DEVICE_NUM; i++) {
		if (cameraChecked[i] == 2) {
			std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

			std::string s(30, '\0');
			std::strftime(&s[0], s.size(), "%Y%m%d_%H%M%S", std::localtime(&now));

			//WriteImage(image[i], "bmp", 0, "D:\\Projects\\BackLightInspect\\QWidget_Halcon_LoadImage\\pic\\pic1.bmp" );

			string filename = ".\\pic\\camera" + std::to_string(i) + "_" + s;
			const char * p = filename.data();
			WriteImage(image[i], "bmp", 0, (HTuple)(p));
			ui.textEdit_status->append(QString::QString("Camera ") + std::to_string(i).data() + " Save Image Success!");

		}
	}

}

void Application::btn_loadcontinuImage_clicked() {

	for (int i = 0; i < DEVICE_NUM; i++) {
		if (cameraChecked[i] == 2)
			camera[i]->continuousGrab();
	}
}

void Application::btn_loadImage_clicked()
{
	for (int i = 0; i < DEVICE_NUM; i++) {
		if (cameraChecked[i] == 2)
			camera[i]->singleGrab();
	}

}


void Application::checkBox_clicked() {

	cameraChecked[0] = ui.checkBox->checkState();
	cameraChecked[1] = ui.checkBox_2->checkState();
	cameraChecked[2] = ui.checkBox_3->checkState();

}

void Application::imageGrabbed(uint8_t * imgBufferPtr, int imgWidth, int imgHeight, int cameraNum) {

	//Basler Camera
	/*//直接用halcon算子转化为HObject 格式	(此算子只适用单个通道)
	 const uint8_t *pImageBuffer = (uint8_t *)ptrGrabResult->GetBuffer();
	GenImage1(&image, "byte", (Hlong)ptrGrabResult->GetWidth(), (Hlong)ptrGrabResult->GetHeight(), (Hlong)pImageBuffer);
	GetImageSize(image, &imgWidth, &imgHeight);*/

	//Luster Camera
	GenImage1(&image[cameraNum], "byte", (Hlong)imgWidth, (Hlong)imgHeight, (Hlong)imgBufferPtr);
	//WriteImage(img, 'tiff', 0, "D://1.tif");
	//WriteImage(image[cameraNum], "bmp", 0, "D:\\1.bmp");
	SetPart(windowHandle[cameraNum], 0, 0, imgHeight, imgWidth);

	if (image[cameraNum].IsInitialized()) {

		DispObj(image[cameraNum], windowHandle[cameraNum]);
		algorithm[cameraNum]->image = image[cameraNum];
		algorithm[cameraNum]->lauchCamera_Thread();
		//algorithm[cameraNum]->processImage();
	}

}

void Application::showImage(int cameraNum) {


	DispObj(algorithm[cameraNum]->imageInvert, windowHandle[cameraNum]);
}







/*******************************************ModbusTCP communication*******************************************************************/
void Application::valueChanged() {

	ui.textEdit_status->append("PLC data at address 0 has changed");

}

void Application::plcDataUpdate() {

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

void Application::btn_send_clicked() {
	if (ui.lineEdit->text().length() != 0) {
		if (client->mtx->try_lock()) {
			//strcpy((char *) client->sendbuf,  ui.lineEdit->text().toLocal8Bit().data());
			client->sendbuf[0] = ui.lineEdit->text().toInt();

			client->mtx->unlock();
		}
	}


}



/*******************************************SQLite*******************************************************************/
void Application::query_returned(int argc, char **argv, char **azColName) {

	QStandardItem *item = 0;

	//int i;
//for (i = 0; i < argc; i++) {
//	printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//}
//printf("\n");


	//for (int i = 0; i < argc; i++) {

	//	item = new QStandardItem(QString::QString(argv[i]));
	//	model_sql_data->setItem(sql->resultCount, i, item);
	//}
	//sql->resultCount++;
//	ui.table_static1->update();
}




/*******************************************Contorller*******************************************************************/

void Application::measure() {

	this->btn_loadImage_clicked();
	product_stat.addOneProduct(std::string("LCM01").data(), MEASURE_RESULT_OK);
	ioc0640->pc_done = true;
	//ui.table_statistic->update();
}
void Application::lightButton_clicked() {
	ioc0640->AUTO_MODE = false;
	if (ioc0640->light_on)
		ioc0640->light_on = false;
	else ioc0640->light_on = true;
}
void Application::LED1Button_clicked() {
	ioc0640->AUTO_MODE = false;

	if (ioc0640->led1_on)
		ioc0640->led1_on = false;
	else ioc0640->led1_on = true;
}
void Application::LED2Button_clicked() {
	ioc0640->AUTO_MODE = false;

	if (ioc0640->led2_on)
		ioc0640->led2_on = false;
	else ioc0640->led2_on = true;
}
void Application::rotateButton_clicked() {
	ioc0640->AUTO_MODE = false;

	if (ioc0640->solenoid_rotateStation->in_closed)
		ioc0640->step1_loadPart = true;
	else if (ioc0640->solenoid_rotateStation->in_opened)
		ioc0640->step2_reload = true;
}

void Application::showAlarm(const char* deviceName, const char* discription) {

	QList<QStandardItem *> items;	//QList is the list of items in one row in the model_alarms

	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	std::string s(30, '\0');
	std::strftime(&s[0], s.size(), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

	QStandardItem *time = new QStandardItem(QString::fromStdString(s));
	time->setForeground(red);
	QStandardItem *device = new QStandardItem(QString::QString(deviceName));
	device->setForeground(red);
	QStandardItem *discrp = new QStandardItem(QString::QString(discription));
	discrp->setForeground(red);

	items.append(time);
	items.append(device);
	items.append(discrp);

	model_alarms->appendRow(items);


}
