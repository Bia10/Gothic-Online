#include "stdafx.h"

CPlayerManager::CPlayerManager()
{
	DLOG("CPlayerManager::CPlayerManager()");

	CAnimation::GetInstance(); //Inicjacja CAnimation
};

CPlayerManager::~CPlayerManager()
{
	DLOG("CPlayerManager::~CPlayerManager()");
};

CLocalPlayer* CPlayerManager::CreateLocalPlayer(int playerID, RakString playerName)
{
	DLOG("CPlayerManager::CreateLocalPlayer(%d, %s)",playerID,playerName.C_String());

	if(playerName.GetLength() <= 30)
	{
		CLocalPlayer* player = new CLocalPlayer(playerID, playerName);
		this->playerList.PushBack(player);
		this->pLocalPlayer = player;
		this->pLocalPlayer->world = core.GetConfig()->GetStartWorld();

		// Crash fix, onInit after create local player
		if (scr.IsScriptLoaded())
			SCallback::onInit();

		return player;
	}
	return NULL;
};

CPlayer* CPlayerManager::CreatePlayer(int playerID, RakString playerName)
{
	DLOG("CPlayerManager::CreatePlayer(%d, %s)",playerID,playerName.C_String());
	if(playerName.GetLength() <= 30)
	{
		CPlayer* player = new CPlayer(playerID, playerName);
		this->playerList.PushBack(player);
		return player;
	}
	return NULL;
};

bool CPlayerManager::DestroyPlayer(CPlayer *player)
{
	DLOG("CPlayerManager::DestroyPlayer()");
	
	if(player != NULL)
	{
		player->UnSpawn();

		this->playerList.Remove(player);
		delete player;
		return true;
	}

	return false;

};

CPlayer* CPlayerManager::GetPlayer(int playerID)
{
	for(unsigned int i = 0; i < this->GetNumberOfPlayers(); ++i)
	{
		if(this->playerList[i]->GetID() == playerID)
			return this->playerList[i];
	}

	return NULL;
};

bool CPlayerManager::IsPlayerSynchronised(oCNpc *npc)
{
	for(unsigned int i = 0; i < this->GetNumberOfPlayers(); ++i)
	{
		if(this->playerList[i]->npc == npc)
			return true;
	}
	return false;
};

CPlayer* CPlayerManager::GetPlayer(oCNpc* npc)
{
	for(unsigned int i = 0; i < this->GetNumberOfPlayers(); i++)
	{
		if(this->playerList[i]->npc == npc)
			return this->playerList[i];
	}
	return NULL;
};

void CPlayerManager::DestroyAllPlayers()
{
	CPlayer* p = NULL;
	for(unsigned int i = 0; i < this->GetNumberOfPlayers(); ++i)
	{
		if( this->playerList[i] && this->playerList[i]->id != core.GetMultiplayer()->GetMyID() )
		{
			p = this->playerList[i];
			p->UnSpawn();
			this->playerList.Remove(p);
			delete p;
		}
	}
};

void CPlayerManager::DestroyAllNpcs()
{
	for( size_t i = 0; i < GetNumberOfPlayers(); ++i )
	{
		if( playerList[i] && playerList[i]->id != core.GetMultiplayer()->GetMyID() )
		{
			if( playerList[i]->npc )
				playerList[i]->UnSpawn();
		}
	}
};

void CPlayerManager::CreateAllNpcs()
{
	for( size_t i = 0; i < GetNumberOfPlayers(); ++i )
	{
		if( playerList[i] && playerList[i]->id != core.GetMultiplayer()->GetMyID() )
		{
			if( !playerList[i]->npc )
				playerList[i]->Spawn(playerList[i]->pos.x, playerList[i]->pos.y+10, playerList[i]->pos.z, playerList[i]->instance);
		}
	}
};

void CPlayerManager::RepairAllPlayers()
{
	if( GetNumberOfPlayers() > 1 )
	{
		for( size_t i = 0; i < GetNumberOfPlayers(); ++i )
		{
			if( playerList[i] && playerList[i]->id != core.GetMultiplayer()->GetMyID() )
			{
				playerList[i]->Repair();
			}
		}
	}
};