/*	Gothic Online ZenGin Research */

#ifndef _ZFILE_H
#define _ZFILE_H

#include "api/g2/ztypes.h"
#include "api/g2/macros.h"

class zFILE
{
public:
	zFILE(const zSTRING& pA){XCALL(0x0043F020)};
	zFILE(void){XCALL(0x0043EFE0)};
	~zFILE(void){XCALL(0x0043F040)};
	static zSTRING __cdecl SetRootDirectory(zSTRING _newDir){XCALL(0x0043E350)};
	static void __cdecl DirectFileConvert(zSTRING& pA){XCALL(0x0043E480)};
	static void __cdecl DirectFileAccess(bool _access){XCALL(0x0043E620)};
	virtual long GetFreeDiskSpace(void){XCALL(0x0043E800)};
	static int __cdecl LockDirScan(void){XCALL(0x0043E810)};
	static int __cdecl UnlockDirScan(void){XCALL(0x0043E830)};
	static void __cdecl DirectFileAccess(bool pA, zSTRING& pB){XCALL(0x0043E850)};
	//static zCBuffer* __cdecl GetFreeBuffer(void){XCALL(0x00443F50)};
	static bool __cdecl InitFileSystem(void){XCALL(0x00444250)};
	static bool __cdecl DeinitFileSystem(void){XCALL(0x004443B0)};

};

class zFILE_FILE : public zFILE
{
public:
	zFILE_FILE(void){XCALL(0x0043F0C0)};
	zFILE_FILE(const zSTRING&){XCALL(0x0043F540)};
	~zFILE_FILE(void){XCALL(0x0043F670)};
	zSTRING GetDirectoryPath(void){XCALL(0x0043F2A0)};
	bool IsOpened(void){XCALL(0x0043F3E0)};
	int Create(const zSTRING& _fileName){XCALL(0x0043F3F0)};
	int Open(const zSTRING& _fileName, bool pB){XCALL(0x0043F450)};
	bool Exists(const zSTRING& _fileName){XCALL(0x0043F4C0)};
	bool Exists(void){XCALL(0x0043F7A0)};
	int Create(void){XCALL(0x0043FAE0)};
	int Open(bool pA){XCALL(0x0043FD80)};
	int Close(void){XCALL(0x00440100)};
	int Reset(void){XCALL(0x00440340)};
	bool Eof(void){XCALL(0x00440370)};
	int Write(char const* text){XCALL(0x004403B0)};
	int Write(const zSTRING& text){XCALL(0x004404F0)};
	int ReadChar(char& pA){XCALL(0x00440730)};
	int __stdcall Read(char* pA){XCALL(0x00440750)};
	int Read(zSTRING& pA){XCALL(0x00440790)};
	int ReadLines(zSTRING& pA, int pB){XCALL(0x00440E20)};
	void SetFilename(zSTRING _newName){XCALL(0x00441F60)};
	void SetExt(zSTRING _newExtension){XCALL(0x004420F0)};
	int SearchFile(const zSTRING& fileName, const zSTRING& path, int pC){XCALL(0x00442B60)};
	bool FileMove(zFILE* file){XCALL(0x00443900)};
	bool FileCopy(zFILE* file){XCALL(0x00443A30)};
	bool FindFirst(const zSTRING& pA){XCALL(0x004431A0)};
};

#endif //_ZFILE_H