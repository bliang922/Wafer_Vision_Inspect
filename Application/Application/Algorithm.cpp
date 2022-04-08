#include "Algorithm.h"

Algorithm::Algorithm(QObject *parent)
	: QObject(parent)
{
}

Algorithm::~Algorithm()
{
}

void Algorithm::lauchCamera_Thread() {
	algorithmThread = std::thread(&Algorithm::processImage, this);
	algorithmThread.detach();
}

void Algorithm::processImage() {
	HalconCpp::InvertImage(image, &imageInvert);
	emit processImageDone(cameraNum);
}


