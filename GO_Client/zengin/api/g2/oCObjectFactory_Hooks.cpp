#include "..\\..\\..\\stdafx.h"
#include <algorithm>
#include <string>

zFILE* oCObjectFactory::Hook_CreateZFile(zSTRING& fileName)
{
	pMemLib->RemoveHook(0x0058BD60);
	std::string s = fileName.ToChar();
	zFILE* result = NULL;
	if( s.find(".sav") != std::string::npos )
	{
		//MessageBox(NULL, "Gothic Online", "Hook", MB_OK);
		s.resize(s.length() - 4);
		s.insert(s.length(), ".gsv");
		result = CreateZFile(zSTRING(s.c_str()));
	}
	else
		result = CreateZFile(fileName);
	pMemLib->ImportHook(0x0058BD60, sizeof(zFILE*(oCObjectFactory::*)(zSTRING&)), &oCObjectFactory::Hook_CreateZFile);
	return result;
};