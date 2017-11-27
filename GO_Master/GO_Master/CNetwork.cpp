#include "stdInc.h"
#define RAKNET_PASSWORD "TEMPORARY_PASSWORD"
CNetwork::CNetwork()
{
	peer = NULL;
};

CNetwork::~CNetwork()
{
	//RakPeerInterface::DestroyInstance(peer);
};

bool CNetwork::Init()
{
	printf("[info] Loading network...\n");
	peer = RakPeerInterface::GetInstance();

	if( peer != NULL )
	{
		printf("[info] Peer set up correctly\n");
		peer->GetLocalIP(0);
		unsigned int numOfAddr = peer->GetNumberOfAddresses();
		SocketDescriptor sd((unsigned short)1200, NULL);
		if( peer->Startup(200, &sd, 1) == RAKNET_STARTED )
		{
			printf("[info] RakNet interface started!\n");
			peer->SetIncomingPassword(RAKNET_PASSWORD, strlen(RAKNET_PASSWORD));
			peer->SetMaximumIncomingConnections((unsigned short)200);

			for(unsigned int i = 0; i < numOfAddr; ++i)
				printf("[info] Listening for connections on %s:%d...\n", peer->GetLocalIP(i), 1200);

			return true;
		}
		else
		{
			printf("[error] Cannot start RakNet!\n");
		}
	}
	else
		printf("[error] Couldn't start new instance of RakPeer!\n");
	return false;
};