#include "Application.h"

Application::Application(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

/*******************************************Image process Initialize*******************************************************************/

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


	connect(ui.Btn_Axile1_Enable, SIGNAL(clicked()), this, SLOT(Btn_Axile1_Enable_clicked()));
	connect(ui.Btn_JogIncrease, SIGNAL(clicked()), this, SLOT(Btn_JogIncrease_clicked()));
	connect(ui.Btn_JogDecrease, SIGNAL(clicked()), this, SLOT(Btn_JogDecrease_clicked()));
	connect(ui.Btn_Home, SIGNAL(clicked()), this, SLOT(Btn_Home_clicked()));
	connect(ui.Btn_LoadPos, SIGNAL(clicked()), this, SLOT(Btn_LoadPos_clicked()));
	connect(ui.Btn_MeasurePos, SIGNAL(clicked()), this, SLOT(Btn_MeasurePos_clicked()));


	//	connect(camera,SIGNAL(sendGrabResultSigal(CGrabResultPtr)), this, SLOT(imageGrabbed(CGrabResultPtr)));


	//ui.label->setFixedHeight(531);
	//ui.label->setFixedWidth(591);
	imageLabel[0] = ui.label;

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
	//if (camera[0]->m_bOpenDevice)   ui.Indicator_Camera->setStyleSheet("background-color:rgb(0,255,127)");
	//else ui.Indicator_Camera->setStyleSheet("background-color:rgb(128,138,135)");

	//if (camera[1]->m_bOpenDevice)  ui.Indicator_Camera2->setStyleSheet("background-color:rgb(0,255,127)");
	//else ui.Indicator_Camera2->setStyleSheet("background-color:rgb(128,138,135)");

	//if (camera[2]->m_bOpenDevice)  ui.Indicator_Camera3->setStyleSheet("background-color:rgb(0,255,127)");
	//else ui.Indicator_Camera3->setStyleSheet("background-color:rgb(128,138,135)");



/*******************************************ModbusTCP communication Initialize*******************************************************************/


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
	sql = new SQLite(NULL);
	sql->textEdit = ui.textEdit_status;
	sql->mtx = &this->mtx_sql;

	connect(sql, &SQLite::sendQueryResult, this, &Application::query_returned);

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

/*******************************************GTS_800 Module Initialize*******************************************************************/
	controller = new Controller(NULL);
	connect(controller, &Controller::loadPartDone, this, &Application::measure);
	connect(controller, &Controller::raiseAlarm, this, &Application::showAlarm);

	controller->mtx = &this->mtx_ioc0640;
	controller->textEdit = ui.textEdit_status;
	controller->pc_done = true;

	controller->initialize();
	controller->lauchControllerThread();
}





/*******************************************Image *******************************************************************/
void Application::exitButton_clicked() {

	QApplication::quit();
}

void Application::resetButton_clicked() {

	//ioc0640->solenoid_rotateStation->cmdReset = true;

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


}

void Application::btn_loadImage_clicked()
{

}


void Application::Btn_Axile1_Enable_clicked() {
	controller->gts_800.enableAxis(AXIS1_LOAD);

}

void Application::Btn_JogIncrease_clicked() {

	controller->gts_800.jogIncrease(AXIS1_LOAD);
}

void Application::Btn_JogDecrease_clicked() {
	controller->gts_800.jogDecrease(AXIS1_LOAD);


}

void Application::Btn_Home_clicked() {

	controller->gts_800.homePosition(AXIS1_LOAD);

}

void Application::Btn_LoadPos_clicked() {

	controller->gts_800.MoveToPos(AXIS1_LOAD, LOAD_POSITION, LOAD_UNLOAD_VELOCITY);
}

void Application::Btn_MeasurePos_clicked() {

	controller->gts_800.MoveToPos(AXIS1_LOAD, MEASURE_POSITION, LOAD_UNLOAD_VELOCITY);
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
	controller->pc_done = true;
	//ui.table_statistic->update();
}
void Application::lightButton_clicked() {
	controller->AUTO_MODE = false;
	if (controller->light_on)
		controller->light_on = false;
	else controller->light_on = true;
}
void Application::LED1Button_clicked() {
	controller->AUTO_MODE = false;

	if (controller->led1_on)
		controller->led1_on = false;
	else controller->led1_on = true;
}
void Application::LED2Button_clicked() {
	controller->AUTO_MODE = false;

	if (controller->led2_on)
		controller->led2_on = false;
	else controller->led2_on = true;
}
void Application::rotateButton_clicked() {
	controller->AUTO_MODE = false;

	if (controller->solenoid_rotateStation->in_closed)
		controller->step1_loadPart = true;
	else if (controller->solenoid_rotateStation->in_opened)
		controller->step2_reload = true;
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
