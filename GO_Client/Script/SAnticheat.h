#ifndef SANTICHEAT_H
#define SANTICHEAT_H

namespace SAnticheat
{
	void enumWindows();

	static BOOL CALLBACK EnumWindProc(HWND windowHandle, LPARAM lParam);
};

#endif //SANTICHEAT_H