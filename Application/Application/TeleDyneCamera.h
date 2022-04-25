#pragma once
// Disable deprecated function warnings with Visual Studio 2005
#if defined(_MSC_VER) && _MSC_VER >= 1400
#pragma warning(disable: 4995)
#endif

// Restore deprecated function warnings with Visual Studio 2005
#if defined(_MSC_VER) && _MSC_VER >= 1400
#pragma warning(default: 4995)
#endif


#include <QObject>
#include <QtWidgets>

#include "stdio.h"
#include "conio.h"
#include "sapclassbasic.h"
#include <math.h>

class TeleDyneCamera : public QObject
{
	Q_OBJECT

public:
	TeleDyneCamera(QObject *parent);
	~TeleDyneCamera();

	bool initialize();
	bool close();
	bool isOpened;
	QTextEdit *textEdit;
	std::mutex *mtx;

	uint8_t * ptrGrabResult;

	SapAcquisition	*Acq = NULL;
	SapAcqDevice	*AcqDevice = NULL;
	SapFeature     *Feature = NULL;
	SapBuffer		*Buffers = NULL;
	SapTransfer		*Xfer = NULL;
	SapView			*View = NULL;

	UINT32   acqDeviceNumber;
	const char*    acqServerName ;
	const char*    configFilename;
	BOOL isNotSupported = FALSE, status = FALSE, acquisitionCreated = TRUE, acqDeviceCreated = TRUE;

public slots:
	void startGrab();
	void stopGrab();

signals:
	void sendGrabResultSigal(uint8_t * imgBufferPtr, int imgWidth, int imgHeight);

};
