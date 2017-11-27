#include "stdafx.h"

CReceiver::CReceiver()
{
	//DLOG("CReceiver::CReceiver()\n");
};

CReceiver::~CReceiver()
{
	//DLOG("CReceiver::~CReceiver()\n");
};

void CReceiver::ReceivePackets(CNetwork *network)
{
	for( Packet* packet = network->GetPeer()->Receive(); packet; network->GetPeer()->DeallocatePacket(packet), packet = network->GetPeer()->Receive() )
	{
		switch(packet->data[0])
		{
		case GO_CONNECTION: 
			ConnectionRPC::HandleConnectionRPC(network,packet); break;
		case GO_LAUNCHER:
			LauncherRPC::HandleLauncherRPC(network,packet); break;
		case GO_CHAT:
			ChatRPC::HandleChatRPC(network,packet); break;
		case GO_PLAYER:
			PlayerRPC::HandlePlayerRPC(network,packet); break;
		case GO_ITEM:
			ItemRPC::HandleItemRPC(network,packet); break;
		case GO_SCRIPT:
			ScriptRPC::HandleScriptRPC(network,packet); break;

		//RakNetowskie, od po³¹czenia
		case ID_NEW_INCOMING_CONNECTION:
			ConnectionRPC::CatchConnection(network,packet); break;
		case ID_CONNECTION_LOST:
			ConnectionRPC::LostConnection(network,packet); break;
		case ID_DISCONNECTION_NOTIFICATION:
			ConnectionRPC::Disconnection(network,packet); break;
		}
	}
};