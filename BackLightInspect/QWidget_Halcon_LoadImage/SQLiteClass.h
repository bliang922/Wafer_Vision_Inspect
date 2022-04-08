#pragma once

#include <QObject>
#include "sqlite3.h"
#include <mutex>
#include <QtWidgets>

class SQLiteClass : public QObject
{
	Q_OBJECT

public:
	sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	const char *sql;
	int resultCount;
	QTextEdit* textEdit;
	std::mutex* mtx;
	bool sql_open;

	SQLiteClass(QObject *parent);
	SQLiteClass();
	~SQLiteClass();

	void initialize();
	void insertRow();
signals:
	void sendQueryResult(int, char **, char **);
};
