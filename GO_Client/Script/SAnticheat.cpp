#include "..\\stdafx.h"

void SAnticheat::enumWindows()
{
	EnumWindows(&SAnticheat::EnumWindProc, NULL);
};

BOOL CALLBACK SAnticheat::EnumWindProc(HWND windowHandle, LPARAM lParam)
{
	char windowText[64];
	GetWindowText(windowHandle, windowText, 64);

	if (SCallback::onProgramName(RakString(windowText).C_String()) == 1)
	{
		CGameManager::GetGameManager()->ExitGame();
		ExitProcess(0);
		return false;
	}
	return true;
};