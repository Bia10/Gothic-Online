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
	*(LPCSTR*)0x00839C14 = (LPCSTR)windowName; //�eby ta opcja dzia�a�a musi zosta� uruchomiona przed zainicjowaniem okna gothica
										//Zmienia tekst w zmiennej APP_NAME na wybran� przez funkcj� nazw�*/
	SetWindowText(GetGothicWindowHandle(), windowName); //Poprawi�, gothic 1 jako� inaczej definiuje nazw� okna
};