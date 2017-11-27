#ifndef CSPLASHSCREEN_H
#define CSPLASHSCREEN_H

class CSplashScreen
{
public:
	CSplashScreen();
	~CSplashScreen();

	static LRESULT CALLBACK SplashWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static DWORD __stdcall InitializeSplashScreen(void * param);
};

#endif //CSPLASHSCREEN_H