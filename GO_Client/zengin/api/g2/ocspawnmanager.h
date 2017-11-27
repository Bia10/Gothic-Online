/* Gothic Online ZenGin research */

#ifndef _OCSPAWNMANAGER_H
#define _OCSPAWNMANAGER_H

#include "api/g2/macros.h"
#include "api/g2/ztypes.h"
#include "api/g2/ocnpc.h"

class oCSpawnManager
{
public:
	void Fake_DeleteNpc(oCNpc* npc);
	int Fake_CheckRemoveNpc(oCNpc* npc);

	oCSpawnManager(void){XCALL(0x006CF4D0)};
	~oCSpawnManager(void){XCALL(0x006CF530)};

	static void SetInsertRange(float){XCALL(0x006CF5D0)};
	static float GetInsertRange(void){XCALL(0x006CF5E0)};
	static void SetRemoveRange(float){XCALL(0x006CF5F0)};
	static float GetRemoveRange(void){XCALL(0x006CF600)};
	void SetSpawnTime(float){XCALL(0x006CF610)};
	float GetSpawnTime(void){XCALL(0x006CF620)};
	void ClearList(void){XCALL(0x006CF630)};
	void SpawnImmediately(int){XCALL(0x006CF800)};
	void CheckInsertNpcs(void){XCALL(0x006CF9A0)};
	void CheckInsertNpc(void){XCALL(0x006CFDE0)};
	oCNpc* SummonNpc(int, const zVEC3&, float){XCALL(0x006D0350)};
	oCNpc* SpawnNpc(int, const zSTRING&, float){XCALL(0x006D0450)};
	void SpawnNpc(oCNpc*, const zSTRING&, float){XCALL(0x006D04C0)};
	void SpawnNpc(oCNpc*, const zVEC3&, float){XCALL(0x006D0710)};
	int CheckRemoveNpc(oCNpc*){XCALL(0x006D0A80)};
	void DeleteNpc(oCNpc*){XCALL(0x006D0DE0)};
	void SetSpawningEnabled(int){XCALL(0x006CF7F0)};

};

#endif //_OCSPAWNMANAGER_H