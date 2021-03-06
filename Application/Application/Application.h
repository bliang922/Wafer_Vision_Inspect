#pragma once

#if defined(_MSC_VER) && (_MSC_VER>=1600)
#pragma execution_character_set("utf-8")
#endif

#include <QtWidgets/QMainWindow>
#include "ui_Application.h"
#include "Controller.h"
#include <QtWidgets/QMainWindow>
#include "HalconCpp.h"
#include "qdebug.h"
#include <qlabel.h>
#include <QSlider.h>
//#include <pylon/PylonIncludes.h>
//Basler camera
//#include "qtCameraClass.h"

//Luster camera
#include "TeleDyneCamera.h"
#include <QMetaType>
#include <QStandardItemModel>
#include "SQLite.h"
#include <stdbool.h>
#include <ctime>
#include <iostream>
#include "ProductionStatistic.h"
#include "Algorithm.h"
#include <QtWidgets>
#include<thread>
#include <bitset>
#include "TeleDyneCamera.h"

using namespace HalconCpp;
using namespace Qt;
// Namespace for using cout.
using namespace std;

// camera number
#define DEVICE_NUM    1


class Application : public QMainWindow
{
    Q_OBJECT

public:
    Application(QWidget *parent = Q_NULLPTR);

private:
    Ui::ApplicationClass ui;


public:

	QLabel *imageLabel[DEVICE_NUM];
	QPoint dragStartPosition;
	HObject image[DEVICE_NUM], imageZoomed;
	Algorithm *algorithm[DEVICE_NUM];
	Hlong windowID[DEVICE_NUM];
	HTuple zoomFactor = 1;
	HTuple windowHandle[DEVICE_NUM];
	HTuple imgWidth, imgHeight;

	//Basler camera
	//qtCameraClass * camera;

	//Luster camera
	TeleDyneCamera *camera[DEVICE_NUM];
	std::mutex mtx_camera, mtx_sql, mtx_modbus, mtx_ioc0640, mtx_algorithm;
	//void zoomImage(HTuple factor, HObject *);
	//void showImage(HObject &image,HTuple& windowHandle);

public slots:
	void btn_startGrab_clicked();
	void btn_stopGrab_clicked();

	//void zoomIn_clicked();
	//void zoomOut_clicked();
	//void normalSize_clicked();
	void exitButton_clicked();
	//void lightButton_clicked();
	//void LED1Button_clicked();
	//void LED2Button_clicked();
	void controller_data_update();
	void saveImageButton_clicked();
	void resetButton_clicked();
	void imageGrabbed(int);
	void measure();
	//void sliderValueChanged(int position);

	//void checkBox_clicked();
	void showImage(int cameraNum);
	
	void Btn_Axile1_Enable_clicked();
	void Btn_JogIncrease_pressed();
	void Btn_JogIncrease_released();
	void Btn_JogDecrease_pressed();
	void Btn_JogDecrease_released();
	void Btn_Home_clicked();
	void Btn_LoadPos_clicked();
	void Btn_MeasurePos_clicked();

	void Btn_Axile2_Enable_clicked();
	void Btn_Home_2_clicked();
	void Btn_JogIncrease2_pressed();
	void Btn_JogIncrease2_released();
	void Btn_JogDecrease2_pressed();
	void Btn_JogDecrease2_released();
	void Btn_Angel1_clicked();
	void Btn_Angel2_clicked();

protected:
	//void mouseMoveEvent(QMouseEvent *event) override;
	/*void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;*/

	//	void wheelEvent(QWheelEvent *event) override;

/************************************SQLite**************************************************************************/
public:
	SQLite *sql;
	ProductionStatistic product_stat;
public slots:
	void query_returned(int, char **, char **);

/************************************Controller**************************************************************************/

public:
	Controller *controller;
	QStandardItemModel *model_sql_data, *model_alarms;


public slots:
	void showAlarm(const char*, const char*);
};
