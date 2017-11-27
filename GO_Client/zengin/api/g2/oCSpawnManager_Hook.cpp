#include "..\\..\\..\\stdafx.h"

void oCSpawnManager::Fake_DeleteNpc(oCNpc* npc)
{
	/*if( playerManager.IsPlayerSynchronised(npc) == true )
		return;
	else
	{
		pMemLib->RemoveHook(0x006D0DE0);
		this->DeleteNpc(npc);
		pMemLib->ImportHook(0x006D0DE0, sizeof(void(oCSpawnManager::*)(oCNpc*)), &oCSpawnManager::Fake_DeleteNpc);
	}*/

	return;
};

int oCSpawnManager::Fake_CheckRemoveNpc(oCNpc* npc)
{
	//Zrobic sprawdzanie czy npc jest zsynchronizowany
	//jesli jest zwrocic false
	//jesli nie, oryginalna funkcje
	/*bool result;
	if( playerManager.IsPlayerSynchronised(npc) == true )
		result = false;
	else
	{
		pMemLib->RemoveHook(0x006D0A80);
		result = this->CheckRemoveNpc(npc);
		pMemLib->ImportHook(0x006D0A80, sizeof(int(oCSpawnManager::*)(oCNpc*)), &oCSpawnManager::Fake_CheckRemoveNpc);
	}
	return result;*/
	return false;
};