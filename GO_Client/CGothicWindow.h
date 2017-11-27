/* GO source file */
#ifndef CGOTHICWINDOW_H
#define CGOTHICWINDOW_H

namespace CGothicWindow
{
	HINSTANCE GetGothicInstance();
	HWND GetGothicWindowHandle();
	RakString GetGothicWindowName();

	void SetGothicWindowName(RakString& windowName);
};


#endif //CGOTHICWINDOW_N