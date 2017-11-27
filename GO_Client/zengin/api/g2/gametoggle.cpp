#include "..\\..\\..\\stdafx.h"

void Fake_HandleResultString(zSTRING str)
{
};

int Hook_Apply_Options_Video()
{
	pMemLib->RemoveHook(0x0042A310);
	if( core.IsLateHooksInitiated() == true )
		core.DeInitializeLateHooks();
	int result = Apply_Options_Video();
	if( core.IsLateHooksInitiated() == false )
		core.InitializeLateHooks();
	pMemLib->ImportHook(0x0042A310, sizeof(int(*)()), &Hook_Apply_Options_Video);
	return result;
};

int ConsoleEval(zSTRING& s, zSTRING& msg)
{
	XCALL(0x00603AE0);
};

int Apply_Options_Video()
{
	XCALL(0x0042A310);
};

void HandleResultString(zSTRING str)
{
	XCALL(0x004301F0);
};

int __cdecl vidGetFPSRate()
{
	XCALL(0x004EF790);
};