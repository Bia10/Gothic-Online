/* Gothic Online source file */
#ifndef CLOG_H
#define CLOG_H

#include "..\\stdafx.h"

#pragma warning(disable:4996)
#include <fstream>

#ifdef DEV_MODE
	#define DLOG(format, ...) \
			CLog::Log(format, __VA_ARGS__)
#else //DEV_MODE
	#define DLOG(format, ...)
#endif //DEV_MODE

#define LOG CLog::Log

enum eTimeStampType
{
	HOUR_MINUTE_SECOND,
	DAY_MONTH_YEAR_HOUR_MINUTE_SECOND
};

class CLog
{
private:
	FILE* logFile;
public:
	CLog();
	~CLog();
	
	static void GetTimeStamp(char* timeStamp, eTimeStampType = HOUR_MINUTE_SECOND);
	static void Log(const char* format, ...);

};

#endif //CLOG_H