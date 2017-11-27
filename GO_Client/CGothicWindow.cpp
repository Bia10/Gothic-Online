#include "stdafx.h"

HINSTANCE CGothicWindow::GetGothicInstance()
{
	return *(HINSTANCE*)0x0086F4AC; //hInstApp
};

HWND CGothicWindow::GetGothicWindowHandle()
{
	return *(HWND*)0x0086F4B8; //hWndApp
};

RakString CGothicWindow::GetGothicWindowName()
{
	char windowName[256];
	GetWindowText(GetGothicWindowHandle(), windowName, sizeof(windowName));
	return windowName;
};

void CGothicWindow::SetGothicWindowName(RakString& windowName)
{
	*(LPCSTR*)0x00839C14 = (LPCSTR)windowName; //¯eby ta opcja dzia³a³a musi zostaæ uruchomiona przed zainicjowaniem okna gothica
										//Zmienia tekst w zmiennej APP_NAME na wybran¹ przez funkcjê nazwê*/
	SetWindowText(GetGothicWindowHandle(), windowName); //Poprawiæ, gothic 1 jakoœ inaczej definiuje nazwê okna
};