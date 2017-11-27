#include "..\\..\\..\\stdafx.h"

void CGameManager::Hook_Menu(int i)
{
	DLOG("CGameManager::Hook_Menu()");
	pMemLib->RemoveHook(0x004279F0); //Tylko usuniêcie hooka, bo ca³a operacja inicjacji jest wykonywana tylko raz
	//Inicjacja gry
	CGothicGame* gothicGame = core.GetGothicGame();
	CNetwork* net = core.GetNetwork();
	
	if( net->IsInitiated() == false )
	{
		gothicGame->InitGame();
	}
};

void CGameManager::Hook_Done()
{
	DLOG("CGameManager::Hook_Done()");
	pMemLib->RemoveHook(0x00424850);
	CNetwork* net = core.GetNetwork();
	if( net )
		if( net->IsConnected() == true )
			net->Disconnect();

	this->Done();
	pMemLib->ImportHook(0x00424850, sizeof(void(CGameManager::*)(void)), &CGameManager::Hook_Done);
};