#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QWidget_Halcon_LoadImage.h"
#include "HalconCpp.h"
#include "qdebug.h"
#include <qlabel.h>
#include <QSlider.h>
//#include <pylon/PylonIncludes.h>
//Basler camera
//#include "qtCameraClass.h"

//Luster camera
#include "LusterCameraClass.h"
#include <QMetaType>
#include <QStandardItemModel>
#include "ClientClass.h"
#include "SQLiteClass.h"
#include "IOC0640_Class.h"

using namespace HalconCpp;
using namespace Qt;
// Namespace for using cout.
using namespace std;

// Number of images to be grabbed.
static const uint32_t c_countOfImagesToGrab = 100;
#define DEVICE_NUM          3

class QWidget_Halcon_LoadImage : public QMainWindow
{
    Q_OBJECT

public:
    QWidget_Halcon_LoadImage(QWidget *parent = Q_NULLPTR);

    Ui::QWidget_Halcon_LoadImageClass ui;

	QLabel *imageLabel[DEVICE_NUM];
	QPoint dragStartPosition;
	HObject image[DEVICE_NUM],imageZoomed;
	Hlong windowID[DEVICE_NUM];
	HTuple zoomFactor=1;
	HTuple windowHandle[DEVICE_NUM];
	HTuple imgWidth, imgHeight;
	
	//Basler camera
	//qtCameraClass * camera;

	//Luster camera
	LusterCameraClass *camera[3];
	std::mutex mtx_camera,mtx_sql,mtx_modbus,mtx_ioc0640;
	MV_CC_DEVICE_INFO_LIST m_stDevList = {0};
	int cameraChecked[DEVICE_NUM];
	//void zoomImage(HTuple factor, HObject *);
	//void showImage(HObject &image,HTuple& windowHandle);

public slots:
	void btn_loadImage_clicked();
	void btn_loadcontinuImage_clicked();

	//void zoomIn_clicked();
	//void zoomOut_clicked();
	//void normalSize_clicked();
	void exitButton_clicked();
	void saveImageButton_clicked();

	void imageGrabbed(uint8_t * , int , int, int );
	void measure();
	//void sliderValueChanged(int position);

	void checkBox_clicked();

//protected:
//	void mouseMoveEvent(QMouseEvent *event) override;
//	void mousePressEvent(QMouseEvent *event) override;
//	void wheelEvent(QWheelEvent *event) override;


/************************************Modbus TCP communication**************************************************************************/
public:
	ClientClass *client;
	QStandardItemModel* model_PLC_IO,* model_sql_data,* model_alarms;
public slots:
	void btn_send_clicked();
	void valueChanged();
	void plcDataUpdate();


/************************************SQLite**************************************************************************/
public:
	SQLiteClass *sql;
public slots:
	void query_returned(int, char **, char **);


/************************************IOC0640**************************************************************************/

public:
	IOC0640_Class ioc0640;
};
