#include "stdafx.h"

CMultiplayer::CMultiplayer()
{
	//DLOG("CMultiplayer::CMultiplayer()\n");
	//tworzenie playermanager i worldmanager
	playerManager; //Zainicjowanie managera
};

CMultiplayer::~CMultiplayer()
{
	//DLOG("CMultiplayer::~CMultiplayer()\n");
	//usuwanie playermanager i worldmanager
};

void CMultiplayer::CreateAllPlayersForPlayer(CPlayer* player)
{
};

void CMultiplayer::CreatePlayerForAllPlayers(CPlayer *player)
{
	for(playerListIter i = playerManager.playerList.begin(); i != playerManager.playerList.end(); ++i)
		if( i->second->GetID() != player->GetID() )
			playerManager.CreatePlayerForOtherPlayer(player, i->second);
};