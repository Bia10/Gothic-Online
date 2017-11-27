#include "stdafx.h"

#define RAKNET_PASSWORD "TEMPORARY_PASSWORD"

CNetwork::CNetwork()
{
	DLOG("CNetwork::CNetwork()");

	bIsInitiated = false;
	bConnected = false;
	peer = NULL;
	pReceiver = new CReceiver();
};

CNetwork::~CNetwork()
{
	DLOG("CNetwork::~CNetwork()");
	/*if(peer)	//Blokuje wy³¹czenie gry powoduj¹c crasha
		RakPeerInterface::DestroyInstance(peer);*/
	delete pReceiver;
};

bool CNetwork::InitNetwork()
{
	DLOG("CNetwork::InitNetwork()");
	
	this->peer = RakPeerInterface::GetInstance();
	if( this->peer )
	{
		SocketDescriptor socketDescriptor;
		if( this->peer->Startup(1,&socketDescriptor,1) == RAKNET_STARTED )
		{
			this->bIsInitiated = true;
			return true;
		}
	}
	return false;
};

void CNetwork::Connect(RakString address, unsigned short port)
{
	DLOG("CNetwork::Connect(%s, %u)", address.C_String(), port);

	if(this->IsConnected() == false)
	{
		if(this->IsInitiated() == true)
			this->GetPeer()->Connect(address, port, RAKNET_PASSWORD, strlen(RAKNET_PASSWORD));
	}
};

void CNetwork::Disconnect()
{
	DLOG("CNetwork::Disconnect()");
	if (playerManager.GetLocalPlayer()) playerManager.GetLocalPlayer()->ReleaseMob();
	this->GetPeer()->CloseConnection(this->GetServerAddress(), true);
	RakSleep(30);
	this->bConnected = false;
};