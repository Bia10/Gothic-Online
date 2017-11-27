/* GO source file */

#include "..\\stdafx.h"

#include <Windows.h>
#include <io.h>
#include <stdarg.h>
#include <time.h>

CLog* pLog = NULL;

void AttachConsole(const char* title)
{
	AllocConsole();
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle,0);
	FILE * hf = _fdopen( hCrt, "w" );
	char buf[2];
	setvbuf( hf, buf, _IONBF, 1 );
	*stdout = *hf;
	SetConsoleTitleA(title);
}

CLog::CLog()
{
	pLog = this;
	#define LOG_FILE "..\\GOLog.txt"
#ifdef DEV_MODE
	AttachConsole("Gothic Online Debug Window");
	int width = 0;
	int height = 0;
	RECT rect;
	if(GetWindowRect(GetConsoleWindow(), &rect))
	{
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
	}
	SetWindowPos(GetConsoleWindow(), NULL, (GetSystemMetrics(SM_CXSCREEN) - width + 100), (height - 340), width, height, 0);
#endif
	
	logFile = fopen(LOG_FILE, "w");
};

CLog::~CLog()
{
	fclose(logFile);
};

void CLog::GetTimeStamp(char* timeStamp, eTimeStampType stampType)
{
	time_t seed = time(0);
	tm t;
	t = *localtime(&seed);
	switch(stampType)
	{
		case HOUR_MINUTE_SECOND:
			sprintf(timeStamp, "%02d:%02d:%02d", t.tm_hour, t.tm_min, t.tm_sec); break;
		case DAY_MONTH_YEAR_HOUR_MINUTE_SECOND:
			sprintf(timeStamp,"%02d-%02d-%d %02d:%02d:%02d",t.tm_mday, t.tm_mon+1, t.tm_year+1900, t.tm_hour,t.tm_min,t.tm_sec); break;
	};
};

void CLog::Log(const char* format, ...)
{
	if(pLog->logFile)
	{
		char date[50];
		char fmtstr[1024];
		
		va_list args;
		va_start(args,format);
		
		time_t seed = time(0);
		tm t;
		t = *localtime(&seed);
		
		vsprintf(fmtstr,format,args); //formatted buff from args list
		sprintf(date,"[%02d:%02d:%02d]",t.tm_hour,t.tm_min,t.tm_sec); //date format
		fprintf(stdout,"%s\n",fmtstr); //put in console
		fprintf(pLog->logFile,"%s %s\n",date,fmtstr); //put in file
		fflush(pLog->logFile);

		va_end(args);
	}
};