#pragma once
#include <QObject>
#include <QtWidgets>
#include <thread>
#include <mutex>
#include "HalconCpp.h"


class Algorithm : public QObject
{
	Q_OBJECT

public:
	Algorithm(QObject *parent);
	~Algorithm();

	int cameraNum;


	std::thread algorithmThread;
	std::mutex* mtx;
	QTextEdit *textEdit;
	HalconCpp::HObject image, imageInvert;

	void lauchCamera_Thread();

	void  processImage();
signals:
	void processImageDone(int cameraNum);
};
