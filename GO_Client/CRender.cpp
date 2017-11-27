#include "stdafx.h"

CRender::CRender()
{
	DLOG("CRender::CRender()");
};

void CRender::Render()
{
	//Wys³anie pakietu o gotowoœci clienta do dzia³ania
	CNetwork* net = core.GetNetwork();
	CGothicGame* gothicGame = core.GetGothicGame();
	if( gothicGame->bIsFirstFrame == true )
	{
		CConfig* config = core.GetConfig();

		if( net -> IsInitiated() == true && net -> IsConnected() == false)
			net -> Connect(config->GetServerIp(), atoi(config->GetServerPort().C_String())); //Nawi¹zywanie po³¹czenia
		gothicGame->bIsFirstFrame = false;
	}
	//Render chat
	CChat* chat = core.GetChat();
	if( chat )
		chat->Render();
	//Receiver/gui debug drawing
	if( net->IsInitiated() == true )
	{
		net->GetReceiver()->ReceivePackets(net);
		CNetInterface::GetInstance().Render(); //Rysowanie GUI z informacjami o sieci
		CPlayerList::GetInstance().Render();
		zCursor::GetCursor().OnUpdate(); //Kursor
		/*oCGame* game = oCGame::GetGame(); //Fix paska zycia
		if (game->GetShowPlayerStatus())
		{
			game->SetShowPlayerStatus(0);
			game->SetShowPlayerStatus(1);
		}*/
	}
	//Connected shitz
	if( net->IsConnected() == true )
	{
		if( playerManager.GetLocalPlayer() != NULL )
			playerManager.GetLocalPlayer()->Pulse();

		core.GetMultiplayer()->RepairDoor();
		playerManager.RepairAllPlayers(); //BRAND NEW!!!

		if( scr.IsScriptLoaded() == true )
			scr.OnRender();

#ifndef DEV_MODE
		//Sprawdzenie czy marvin nie jest aktywny
		if (!scr.GetScriptVars()->isMarvinEnabled && oCGame::GetGame()->game_testmode)
		{
			CGameManager::GetGameManager()->ExitGame();
			ExitProcess(0);
		}
#endif //DEV_MODE
	}
};