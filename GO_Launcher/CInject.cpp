#define _WIN32_WINNT 0x0501 // WinXP only
#define VC_EXTRALEAN
#include <Windows.h>
#include <TlHelp32.h>
#include <comdef.h>

#include "CInject.h"

// Cancel unicode, only way in Qt
#define Process32First Process32First
#define Process32Next Process32Next
#define PROCESSENTRY32 PROCESSENTRY32

unsigned CInject::GetIndexOfAddress(DWORD oldFunction)
{
	for (unsigned i = 0; i < hookList.size(); ++i)
	{
		if (hookList.at(i)->address == oldFunction)
			return i;
	}

	return 0;
}

DWORD CInject::RunApplication(const char *path)
{
    STARTUPINFOA startupInfo;
	PROCESS_INFORMATION procInfo;
	ZeroMemory(&startupInfo, sizeof(startupInfo));
	startupInfo.cb = sizeof(startupInfo);

    if (CreateProcessA(path, NULL, NULL, NULL, false, NULL, NULL, NULL, &startupInfo, &procInfo))
        return procInfo.dwProcessId;

    return 0;
}

DWORD CInject::GetPID(const char *processName)
{
    PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(hProcessSnapshot, &processInfo))
	{
        while (Process32Next(hProcessSnapshot, &processInfo))
		{
            if (strcmp(processName, processInfo.szExeFile) == 0)
			{
				CloseHandle(hProcessSnapshot);
				return processInfo.th32ProcessID;
			}
		}
	}

	CloseHandle(hProcessSnapshot);
	return 0;
}

bool CInject::InjectDLL(DWORD processID, const char *path)
{
    if (processID)
	{
		FILE *file = fopen(path, "r");
		if (file)
		{
			fclose(file);

			LPVOID kernel;
			LPVOID handleLibrary;
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);

			if (hProcess)
			{
                kernel = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
				handleLibrary = VirtualAllocEx(hProcess, NULL, strlen(path), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
				WriteProcessMemory(hProcess, (LPVOID)handleLibrary, path, strlen(path), NULL);
				CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)kernel, (LPVOID)handleLibrary, NULL, NULL);
				CloseHandle(hProcess);

				return true;
			}
		}
    }

    return false;
}

bool CInject::IsAddressHooked(DWORD oldFunction)
{
	for (unsigned i = 0; i < hookList.size(); i++)
	{
		if (hookList.at(i)->address == oldFunction)
			return true;
	}
	return false;
}

bool CInject::ImportHook(DWORD oldFunction, size_t sizeNewFunction, ...)
{
	if (sizeNewFunction == sizeof(void*))
	{
		if (IsAddressHooked(oldFunction) == false)
		{
			va_list args;
			va_start(args, sizeNewFunction);
			DWORD function = (DWORD)va_arg(args, void*);
			va_end(args);

			Hook* pHook = new Hook;
			pHook->address = oldFunction;

			BYTE jmp[6] = { 0xE9, //jmp
							0x00, 0x00, 0x00, 0x00, //address
							0xC3 }; //retn

			//Read backup
			ReadProcessMemory(GetCurrentProcess(), (LPVOID)oldFunction, pHook->backup, 6, 0);

			DWORD dwCalc = (function - oldFunction - 5);
			memcpy(&jmp[1], &dwCalc, 4);
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)oldFunction, jmp, 6, 0);

			//Add hook to list
			hookList.push_back(pHook);

			return true;
		}
	}

	return false;
}

bool CInject::RemoveHook(DWORD oldFunction)
{
	if (IsAddressHooked(oldFunction))
	{
		//Return backup
		unsigned int index = GetIndexOfAddress(oldFunction);
		WriteProcessMemory(GetCurrentProcess(), (LPVOID)oldFunction, hookList.at(index)->backup, 6, 0);

		//Remove hook from list
		hookList.erase(hookList.begin() + index);

		return true;
	}

	return false;
}
