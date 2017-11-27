#include "stdafx.h"

#define PICTURE_WIDTH 514
#define PICTURE_HEIGHT 228

HINSTANCE hInst = NULL;
const static char * WndClassName = "GoSplash";
const char* GoModuleName = "GO.dll";

CSplashScreen::CSplashScreen()
{
	DLOG("CSplashScreen::CSplashScreen()");

	//Paczowanie splash screena
	pMemLib->WriteJMP(0x4257A0, (unsigned long)CSplashScreen::InitializeSplashScreen);
};

CSplashScreen::~CSplashScreen()
{
	DLOG("CSplashScreen::~CSplashScreen()");
};

LRESULT CALLBACK CSplashScreen::SplashWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_CREATE:
		
		HRSRC RsrcHand; 
		RsrcHand = FindResourceA(GetModuleHandleA(GoModuleName), "RANGE", "RGN"); 
		HGLOBAL RsrcPoint;
		RsrcPoint = LoadResource(GetModuleHandleA(GoModuleName), RsrcHand);
		DWORD RsrcSize;
		RsrcSize = SizeofResource(GetModuleHandleA(GoModuleName), RsrcHand);
		RsrcPoint = LockResource(RsrcPoint);
		SetWindowRgn(hWnd, ExtCreateRegion(NULL, RsrcSize, (LPRGNDATA)RsrcPoint), true);
			  break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
			
			SendMessage(hWnd, WM_DESTROY, wParam, lParam);
			break;
	default: return DefWindowProcA(hWnd, message, wParam, lParam);
	}
	return NULL;
};

DWORD __stdcall CSplashScreen::InitializeSplashScreen(void * param)
{
	DLOG("CSplashScreen::InitializeSplashScreen()");

	hInst = GetModuleHandleA(NULL);
	WNDCLASSEXA wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW |CS_VREDRAW |CS_BYTEALIGNWINDOW;
	wc.hInstance = hInst;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	HBITMAP bitmap = LoadBitmapA(GetModuleHandleA(GoModuleName), MAKEINTRESOURCEA(1000));
	wc.hbrBackground = CreatePatternBrush(bitmap);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WndClassName;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIconSm = NULL;
	wc.lpfnWndProc = CSplashScreen::SplashWndProc;

	RegisterClassExA(&wc);
	
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int wndposx = (screenWidth/2) - (PICTURE_WIDTH/2);
	int wndposy = (screenHeight/2) - (PICTURE_HEIGHT/2);

	HWND hwindow = CreateWindowExA(WS_EX_LEFT|WS_EX_TOOLWINDOW, WndClassName, "", WS_POPUP, wndposx, wndposy, PICTURE_WIDTH, PICTURE_HEIGHT, 0, 0, hInst, 0);
	ShowWindow(hwindow, SW_SHOWNORMAL);
	UpdateWindow(hwindow);

	MSG msg;
	while(GetMessage( &msg, 0, 0, 0 ))
	{ 
		DispatchMessage(&msg); 
		RakSleep(3);
	}
	return NULL;
};