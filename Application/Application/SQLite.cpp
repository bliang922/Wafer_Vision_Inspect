#include "SQLite.h"

SQLite *classPointer = NULL;

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");

	emit classPointer->sendQueryResult(argc, argv, azColName);
	return 0;
}

SQLite::SQLite(QObject *parent)
	: QObject(parent)
{

}

SQLite::SQLite()
{
}


SQLite::~SQLite()
{
}


void SQLite::initialize() {

	classPointer = this;
	/* Open database */
	rc = sqlite3_open("test.db", &db);
	if (rc) {
		textEdit->append(QString("Can't open database: ") + sqlite3_errmsg(db));
	}
	else {
		textEdit->append(QString("Opened database successfully"));
		sql_open = true;
	}

	/* Create SQL statement */
	sql = "CREATE TABLE PRODUCTION("  \
		"TIME TEXT PRIMARY KEY     NOT NULL," \
		"TOTAL           INT    NOT NULL," \
		"OK_TOTAL            INT     NOT NULL," \
		"NG_TOTAL            INT     NOT NULL," \
		"OK_RATE            REAL     NOT NULL," \
		"SHIFT			  TEXT );";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		textEdit->append(QString("SQL error: ") + zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		textEdit->append(QString("Table created successfully"));
	}


	/* SQL statement insert */
	sql = "INSERT INTO PRODUCTION (TIME,TOTAL,OK_TOTAL,NG_TOTAL,OK_RATE,SHIFT)"\
		"VALUES('1-9',50,48,2,98.0,'DayShift');"\
		"INSERT INTO PRODUCTION (TIME,TOTAL,OK_TOTAL,NG_TOTAL,OK_RATE,SHIFT)"\
		"VALUES('10-19',52,50,2,97.0,'DayShift');"\
		"INSERT INTO PRODUCTION (TIME,TOTAL,OK_TOTAL,NG_TOTAL,OK_RATE,SHIFT)"\
		"VALUES('20-29',54,49,5,96.0,'NightShift');";

	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		textEdit->append(QString("SQL error: ") + zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		textEdit->append(QString("Table insert successfully"));
	}

	sql = "SELECT * from PRODUCTION";
	resultCount = 0;
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		textEdit->append(QString("SQL error: ") + zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		textEdit->append(QString("Select operation successfully"));
	}

	sqlite3_close(db);
}
