#include "stdafx.h"

CPlayerManager::CPlayerManager()
{
	//DLOG("CPlayerManager::CPlayerManager()\n");
	timerBroadcastList = 0;
	playerList.clear();
};

CPlayerManager::~CPlayerManager()
{
	//DLOG("CPlayerManager::~CPlayerManager()\n");
	playerList.clear(); //Mo¿na daæ pentelkê co usunie wszystkich graczy
};							  //delete player. ale to nie ma sensu w tym kontekscie

bool CPlayerManager::IsNicknameUsed(RakString playerName)
{
	for(playerListIter i = playerList.begin(); i != playerList.end(); ++i )
	{
		if( i->second->name.StrCmp(playerName) == 0 )
			return true;
	}
	return false;
};

bool CPlayerManager::IsPlayerInManager(CPlayer* player)
{
	for(playerListIter i = playerList.begin(); i != playerList.end(); ++i)
	{
		if(i->second == player)
			return true;
	}
	return false;
};

CPlayer* CPlayerManager::CreatePlayer(SystemAddress address, RakString playerName)
{
	//DLOG("CPlayerManager::CreatePlayer( ,%s)", playerName.C_String());
	if(playerName.GetLength() <= 30)
	{
		int playerId = (int)address.systemIndex;
		CPlayer* player = new CPlayer(address, playerId, playerName);
		playerList[playerId] = player;
		player->bConnected = true;

		return player;
	}
	return NULL;
};

void CPlayerManager::CreatePlayerForOtherPlayer(CPlayer* player, CPlayer* receiver)
{	
	//DLOG("CPlayerManager, Creating player %s for player %s\n", player->name.C_String(), receiver->name.C_String());

	CNetwork* network = core.GetNetwork();
	if(player->spawned)
	{
		std::cout << player->name.C_String() << " armor " << player->armorInstance.C_String() << std::endl;

		BitStream stream;
		stream.Write((MessageID)GO_PLAYER);
		stream.Write((MessageID)CREATE_AND_SPAWN);
		stream.Write(player->playerId);
		stream.Write(player->name);
		stream.Write(player->instance);
		stream.Write(player->bodyModel);
		stream.Write(player->bodyTexture);
		stream.Write(player->headModel);
		stream.Write(player->headTexture);
		/*stream.Write(player->protection[0]);
		stream.Write(player->protection[1]);
		stream.Write(player->protection[2]);
		stream.Write(player->protection[3]);*/
		stream.Write(player->x);
		stream.Write(player->y);
		stream.Write(player->z);
		stream.Write(player->angle);
		stream.Write(player->maxhealth);
		stream.Write(player->health);
		stream.Write(player->armorInstance);
		stream.Write(player->rangedWeaponInstance);
		stream.Write(player->meleeWeaponInstance);
		stream.Write(player->weaponMode);
		stream.Write(player->leftHand);
		stream.Write(player->rightHand);

		network->GetPeer()->Send(&stream, LOW_PRIORITY, RELIABLE, 0, receiver->GetAddress(),false);

		stream.Reset();

		for (int i = 0; i < player->overlaysList.Num(); ++i)
		{
			stream.Write((MessageID)GO_PLAYER);
			stream.Write((MessageID)SET_OVERLAY);
			stream.Write(player->GetID());
			stream.Write(true);
			stream.Write(player->overlaysList.GetElementByIndex(i));

			network->GetPeer()->Send(&stream, LOW_PRIORITY, RELIABLE, 0, receiver->GetAddress(), false);

			stream.Reset();
		}

		for (int i = 0; i < player->timedOverlays.Num(); ++i)
		{
			stream.Write((MessageID)GO_PLAYER);
			stream.Write((MessageID)SET_OVERLAY);
			stream.Write(player->GetID());
			stream.Write(true);
			stream.Write(player->overlaysList.GetElementByIndex(i));

			network->GetPeer()->Send(&stream, LOW_PRIORITY, RELIABLE, 0, receiver->GetAddress(), false);

			stream.Reset();
		}
	}
	else
	{
		BitStream stream;
		stream.Write((MessageID)GO_PLAYER);
		stream.Write((MessageID)CREATE_PLAYER);
		stream.Write(player->playerId);
		stream.Write(player->name);
		network->GetPeer()->Send(&stream,LOW_PRIORITY,RELIABLE,0,receiver->GetAddress(),false);
	}

};

bool CPlayerManager::DestroyPlayer(CPlayer *player)
{
	if(this->IsPlayerInManager(player) == true)
	{
		BitStream stream;
		stream.Write((MessageID)GO_PLAYER);
		stream.Write((MessageID)DESTROY_PLAYER);
		stream.Write(player->GetID());

		player->spawned = false;

		for(playerListIter i = playerList.begin(); i != playerList.end(); ++i)
		{
			if(i->second->GetID() != player->GetID())
			{
				CStreamer* streamer = core.GetStreamer();
				if( streamer->IsPlayerStreamedToPlayer(player, i->second) == true )
				{
					core.GetNetwork()->GetPeer()->Send(&stream,LOW_PRIORITY,RELIABLE,0,i->second->GetAddress(),false);
					i->second->streamedPlayers.Remove(player);
				}
			}
		}
		playerList.erase(player->GetID());
		delete player;
	}

	return false;
};

void CPlayerManager::CheckPlayersTimedOverlays()
{
	for (playerListIter i = playerList.begin(); i != playerList.end(); ++i)
	{
		i->second->CheckTimedOverlay();
	}
}

CPlayer* CPlayerManager::GetPlayer(int playerID)
{
	if( playerList.find(playerID) != playerList.end() )
		return playerList[playerID];
	return NULL;
};

CPlayer* CPlayerManager::GetPlayer(SystemAddress clientAddress)
{
	for(playerListIter i = playerList.begin(); i != playerList.end(); ++i)
		if(i->second->GetAddress() == clientAddress)
			return i->second;
	return NULL;
};

CPlayer* CPlayerManager::GetPlayer(RakString playerName)
{
	for(playerListIter i = playerList.begin(); i != playerList.end(); ++i)
		if( i->second->name.StrCmp(playerName) == 0 )
			return i->second;
	return NULL;
};

void CPlayerManager::BroadcastPlayerList()
{
	if( timerBroadcastList < GetTimeMS() )
	{
		if( this->GetNumberOfPlayers() > 0 )
		{
			char PlayerList[1024][100];
			memset(&PlayerList, 1024, 0);
			CPlayer* player = NULL;
			size_t j = 0;
			for(playerListIter i = playerList.begin(); i != playerList.end(); ++i, ++j)
			{
				player = i->second;
				sprintf(&PlayerList[j][0], "(ID:%d) %s", player->GetID(), player->name.C_String());
			}
			BitStream s;
			s.Write((MessageID)GO_PLAYER);
			s.Write((MessageID)PLAYER_LIST);
			s.Write(PlayerList);

			core.GetNetwork()->SendToAll(s, LOW_PRIORITY, RELIABLE);
		}
		timerBroadcastList = GetTimeMS() + 10000;
	}
};