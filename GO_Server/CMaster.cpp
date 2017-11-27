#include "stdafx.h"
#define RAKNET_PASSWORD "TEMPORARY_PASSWORD"
CMaster::CMaster()
{
	peer = RakPeerInterface::GetInstance();
	timeRefreshMaster = 0;
	isConnected = false;
	SocketDescriptor sd;
	if( peer->Startup(1, &sd, 1) == RAKNET_STARTED )
		LOG("[info] CMaster peer started");
};

CMaster::~CMaster()
{
	peer->Shutdown(300);
};

void CMaster::Pulse()
{
	static bool wasAdded = false;

	if( timeRefreshMaster < GetTimeMS() )
	{
		if (!wasAdded) LOG("[master] Adding server to master list");

		//LOG("[master] New peer instance started");
		peer->Connect("185.5.97.181",(unsigned short)1200, RAKNET_PASSWORD, strlen(RAKNET_PASSWORD));
		for (Packet *packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive())
		{
			if( packet )
			{
				if( packet->data[0] == ID_CONNECTION_REQUEST_ACCEPTED )
				{
					CConfig* cfg = core.GetConfig();
					unsigned int port, maxSlots;
					port = (unsigned int)atoi(cfg->GetServerPort().C_String());
					maxSlots = (unsigned int)atoi(cfg->GetMaxSlots().C_String());

					BitStream s;
					s.Write((MessageID)GO_MASTER);
					s.Write(port);
					s.Write(cfg->GetServerName());
					s.Write(playerManager.GetNumberOfPlayers());
					s.Write(maxSlots);
					s.Write(core.GetDescription());
					s.Write(cfg->GetClientScript());
					s.Write(RakString(versionString));
					s.Write(core.GetWorld());

					if (peer->Send(&s, HIGH_PRIORITY, RELIABLE, 0, packet->systemAddress, false) && !wasAdded)
					{
						wasAdded = true;
						LOG("[master] Server has been added to list!");
					}

					peer->CloseConnection(packet->systemAddress,true);
				}
				else if( packet->data[0] == ID_CONNECTION_ATTEMPT_FAILED || packet->data[0] == ID_DISCONNECTION_NOTIFICATION || packet->data[0] == ID_ALREADY_CONNECTED )
				{
					//if (!wasAdded) LOG("[error] Cannot add server to master list! Connection attempt failure");
					peer->CloseConnection(packet->systemAddress,false);
				}
			}
			RakSleep(1);
		}
		timeRefreshMaster = GetTimeMS() + 60000;
	}
};