#include "../stdafx.h"

void go_log(const char* format, ...)
{
	va_list args;
	va_start(args,format);
	char fmtstr[1024];
	vsprintf(fmtstr,format,args);
	FILE* plik = fopen("GO_Log.txt", "a");
	if( plik )
	{
		fprintf(plik, "%s\n", fmtstr);
		fclose(plik);
	}
	fprintf(stdout, "%s\n", fmtstr);
	va_end(args);
}