#pragma once

#if defined(_MSC_VER) && (_MSC_VER>=1600)
#pragma execution_character_set("utf-8")
#endif


#include "productionstatistic_global.h"
#include <QStandardItemModel>
#include <ctime>
#include <string>

typedef enum _MEASURE_RESULT_
{
	MEASURE_RESULT_NG = 0,
	MEASURE_RESULT_OK = 1,
}MEASURE_RESULT;

typedef enum _WORK_SHIFT_
{
	DAY_SHIFT = 1,
	NIGHT_SHIFT =0,
}WORK_SHIFT;

typedef struct _HOUR_STATISTIC_ {
	int total;
	int ok_total;
	int ng_total;
	double ok_rate;
	WORK_SHIFT shift;
}HOUR_STATISTIC;

typedef struct _DAY_STATISTIC_ {
	int total;
	int ok_total;
	int ng_total;
	double ok_rate;
}DAY_STATISTIC;


class PRODUCTIONSTATISTIC_EXPORT ProductionStatistic
{
private:
//	std::time_t *now;
	int dayShift_start;
	int dayShift_end;
	HOUR_STATISTIC hour_statistic[24];
	DAY_STATISTIC day_statistic;
	QList<QStandardItem *> table_row_items[25];

	std::string time_section[24] = {
		"00:00--01:00",
		"01:00--02:00",
		"02:00--03:00",
		"03:00--04:00",
		"04:00--05:00",
		"05:00--06:00",
		"06:00--07:00",
		"07:00--08:00",
		"08:00--09:00",
		"09:00--10:00",
		"10:00--11:00",
		"11:00--12:00",
		"12:00--13:00",
		"13:00--14:00",
		"14:00--15:00",
		"15:00--16:00",
		"16:00--17:00",
		"17:00--18:00",
		"18:00--19:00",
		"19:00--20:00",
		"20:00--21:00",
		"21:00--22:00",
		"22:00--23:00",
		"23:00--00:00",
	};
public:
    ProductionStatistic();

	QStandardItemModel model_productData;

	void addOneProduct(const char * productModel, int result);
	void setDayShiftRange(int start, int end);
	int getCurrentTimeSection();
	WORK_SHIFT getWorkShift(int);
	
};
