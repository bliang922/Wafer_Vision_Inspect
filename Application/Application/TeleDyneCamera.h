#pragma once

#include <QObject>

class TeleDyneCamera : public QObject
{
	Q_OBJECT

public:
	TeleDyneCamera(QObject *parent);
	~TeleDyneCamera();
};
