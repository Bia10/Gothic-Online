#include "stdafx.h"

#define RAKNET_PASSWORD "TEMPORARY_PASSWORD"

CNetwork::CNetwork()
{
	//DLOG("CNetwork::CNetwork()\n");
	peer = NULL;
	pReceiver = new CReceiver();
};

CNetwork::~CNetwork()
{
	//DLOG("CNetwork::~CNetwork()\n");
	//RakPeerInterface::DestroyInstance(peer);
	//peer->Shutdown(300);
	delete pReceiver;
};

bool CNetwork::InitNetwork()
{
	//LOG("CNetwork::InitNetwork()\n");
	this->peer = RakPeerInterface::GetInstance();
	if( this->peer != NULL )
	{
		CConfig* config = core.GetConfig();
		this->peer->GetLocalIP(0);
		unsigned int uiAddr = this->peer->GetNumberOfAddresses();
		SocketDescriptor socketDescriptor((unsigned short)atoi(config->GetServerPort().C_String()), NULL);
		StartupResult result = this->peer->Startup((unsigned int)atoi(config->GetMaxSlots().C_String())+20, &socketDescriptor, 1);
		if(result == RAKNET_STARTED) 
		{
			this->peer->SetIncomingPassword(RAKNET_PASSWORD, strlen(RAKNET_PASSWORD));
			this->peer->SetMaximumIncomingConnections((unsigned short)atoi(config->GetMaxSlots().C_String())+20);

			for(unsigned int i = 0; i < uiAddr; ++i)
				LOG("[info] Listening for connections on %s:%s...", this->peer->GetLocalIP(i), config->GetServerPort().C_String());
			return true;
		}
		else
		{
			for(unsigned int i = 0; i < uiAddr; ++i)
				LOG("[error] Couldn't listen on %s:%s", this->peer->GetLocalIP(i), config->GetServerPort().C_String());
			CNetworkError::DisplayDetails(result);
		}
	}
	else
		LOG("[error] Couldn't start new instance of RakPeer");

	return false;
};

void CNetwork::SendToAll(BitStream &stream, PacketPriority priority, PacketReliability reliability)
{
	for(playerListIter i = playerManager.playerList.begin(); i != playerManager.playerList.end(); ++i)
		this->GetPeer()->Send(&stream,priority,reliability,0,i->second->GetAddress(),false);
};

void CNetwork::SendToPlayersOnList(BitStream &stream, PacketPriority priority, PacketReliability reliability, List<CPlayer*> *targetPlayerList)
{
	for(unsigned int i = 0; i < targetPlayerList->Num(); ++i)
		this->GetPeer()->Send(&stream,priority,reliability,0,(*targetPlayerList)[i]->GetAddress(),false);
};

void CNetwork::SendToAllWithoutPlayer(BitStream& stream, PacketPriority priority, PacketReliability reliability, CPlayer* player)

{
	for(playerListIter i = playerManager.playerList.begin(); i != playerManager.playerList.end(); ++i)
	{
		if( i->first != player->GetID()) 
		{
			if( strcmp(i->second->world.C_String(), player->world.C_String()) == 0 ) //Sprawdzanie czy swiat jest taki sam iksde
				this->GetPeer()->Send(&stream,priority,reliability,0,i->second->GetAddress(),false);
		}
	}
};

void CNetwork::SendToAllInWorld(BitStream& stream, PacketPriority priority, PacketReliability reliability, RakString world, CPlayer *player)
{
	if (player)
	{
		for (playerListIter i = playerManager.playerList.begin(); i != playerManager.playerList.end(); ++i)
		{
			if (i->first != player->GetID() && strcmp(i->second->world.C_String(), world.C_String()) == 0)
				this->GetPeer()->Send(&stream, priority, reliability, 0, i->second->GetAddress(), false);
		}
	}
	else
	{
		for(playerListIter i = playerManager.playerList.begin(); i != playerManager.playerList.end(); ++i)
		{
			if(strcmp(i->second->world.C_String(), world.C_String()) == 0 )
				this->GetPeer()->Send(&stream,priority,reliability,0,i->second->GetAddress(),false);
		}
	}
};