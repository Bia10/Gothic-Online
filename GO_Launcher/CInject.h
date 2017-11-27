#ifndef __CINJECT_H__
#define __CINJECT_H__

#include <Windows.h>
#include <vector>

class CInject
{
public:
	DWORD RunApplication(const char *path);
	DWORD GetPID(const char *processName);
	bool InjectDLL(DWORD processID, const char *path);
	bool IsAddressHooked(DWORD oldFunction);
	bool ImportHook(DWORD startAddress, size_t size, ...);
	bool RemoveHook(DWORD startAddress);

private:
	struct Hook
	{
		DWORD address;
		unsigned char backup[6];
	};

	unsigned GetIndexOfAddress(DWORD oldFunction);

	std::vector<Hook*> hookList;
};

#endif