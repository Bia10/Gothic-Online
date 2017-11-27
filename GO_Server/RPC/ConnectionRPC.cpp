#include "../stdafx.h"

void ConnectionRPC::HandleConnectionRPC(CNetwork* network, Packet* packet)
{
	BitStream stream(packet->data, packet->length, false);
	stream.IgnoreBytes(1);

	MessageID eConnectionRPC;
	stream.Read(eConnectionRPC);

	if(eConnectionRPC == PLEASE_CONNECT)
		PleaseConnect(network,stream,packet->systemAddress);
};

void ConnectionRPC::CatchConnection(CNetwork* network, Packet* packet)
{
	LOG("[connection] %s is trying to connect, index : %d", packet->systemAddress.ToString(true, '_'), packet->systemAddress.systemIndex);
};

void ConnectionRPC::LostConnection(CNetwork* network, Packet* packet)
{
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);
	if( player )
	{
		SCallback::onDisconnect(player->GetID(), "LOST_CONNECTION");
		player->spawned = false;
		LOG("[connection] %s lost connection with the server %s",player->name.C_String(),player->GetAddress().ToString());
		player->Disconnect();
		playerManager.DestroyPlayer(player);
	}
	else
		network->GetPeer()->CloseConnection(packet->systemAddress,true);
};

void ConnectionRPC::Disconnection(CNetwork* network, Packet* packet)
{
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);
	if( player )
	{
		SCallback::onDisconnect(player->GetID(), "DISCONNECTED");
		player->spawned = false;
		LOG("[connection] %s disconnected from server %s",player->name.C_String(),player->GetAddress().ToString());

		player->Disconnect();
		playerManager.DestroyPlayer(player);
	}
	else
		network->GetPeer()->CloseConnection(packet->systemAddress,true);

};

void ConnectionRPC::PleaseConnect(CNetwork* network, BitStream& stream, SystemAddress clientAddress)
{
	LOG("[connection] Incoming connection: %s",clientAddress.ToString());

	int versionNum;
	RakString playerName;
	RakString dllHash;
	stream.Read(versionNum);
	stream.Read(dllHash);
	stream.Read(playerName);

	//Tu powinno byc sprawdzenie wersji klienta
	if( versionNum == versionNumber && strcmp("f7db305af405e4e3b2326aa84a01c39b", dllHash.C_String()) == 0 )
	{
		dllHash.FreeMemory();
		//Sprawdzenie czy serwer nie jest pe³ny
		if(playerManager.GetNumberOfPlayers() != atoi(core.GetConfig()->GetMaxSlots().C_String()))
		{
			//Sprawdzenie czy nick nie jest zajêty										//Nick zablokowany, zeby nikt nie podszywal sie
			if(playerManager.IsNicknameUsed(playerName) == false && playerName.StrCmp("(SERVER)") != 0) //pod konsole
			{
				CPlayer* player = playerManager.CreatePlayer(clientAddress,playerName);
				if( player )
				{
					stream.Read(player->world);
					stream.Read(player->x);
					stream.Read(player->y);
					stream.Read(player->z);

					//Akceptowanie po³¹czenia
					BitStream bStream;
					bStream.Write((MessageID)GO_CONNECTION);
					bStream.Write((MessageID)ACCEPT_CONNECTION);
					bStream.Write(core.GetConfig()->GetServerName());
					bStream.Write(player->GetID());
					// Hour/minute
					bStream.Write(core.GetHour());
					bStream.Write(core.GetMinute());
					bStream.Write(core.GetDay());
					// Unconscious
					bStream.Write(core.GetUnconscious());
					network->GetPeer()->Send(&bStream,LOW_PRIORITY,RELIABLE,0,clientAddress,false);

					bStream.Reset();

					//Tworzenie gracza dla wszystkich i wszystkich dla gracza
					/*CMultiplayer* m = core.GetMultiplayer();
					m->CreateAllPlayersForPlayer(player);
					m->CreatePlayerForAllPlayers(player);*/

					playerManager.CreatePlayerForOtherPlayer(player, player);
					playerManager.BroadcastPlayerList();
		
					player->spawned = true;
					SCallback::onJoin(player->GetID());

				LOG("[join] %s has joined the server %s",playerName.C_String(),player->GetAddress().ToString());
#ifdef DEV_MODE
				LOG("[debug] Player dll hash: %s", dllHash.C_String());
#endif
				//Ask player for correct script's hashes
				BitStream sStream;
				sStream.Write((MessageID)GO_SCRIPT);
				sStream.Write((MessageID)SCRIPT_CHECK);
				sStream.Write(core.GetConfig()->GetClientScript());
				md5wrapper wrap;
				std::string checksum = "NULL";
				char buff[512];
				sprintf(buff, "client-scripts/%s", core.GetConfig()->GetClientScript().C_String());
				FILE* file = fopen(buff, "r");
				if( file )
				{
					fclose(file);
					checksum = wrap.getHashFromFile(std::string(buff));
				}
				sStream.Write(RakString(checksum.c_str()));
				//network->GetPeer()->Send(&sStream, LOW_PRIORITY, RELIABLE, 0, clientAddress, false); //DISABLED ONLY FOR TESTS!!
				}
			}
			else
				NicknameUsed(network,clientAddress);
		}
		else
			ServerFull(network,clientAddress);

	}	
	else 
		IncorrectVersion(network,clientAddress);

};

//Send
void ConnectionRPC::IncorrectVersion(CNetwork* network, SystemAddress clientAddress)
{
	BitStream stream;
	stream.Write((MessageID)GO_CONNECTION);
	stream.Write((MessageID)INCORRECT_VERSION);
	network->GetPeer()->Send(&stream,LOW_PRIORITY,RELIABLE,0,clientAddress,false);
	network->GetPeer()->CloseConnection(clientAddress,true);

};

void ConnectionRPC::ServerFull(CNetwork* network, SystemAddress clientAddress)
{
	BitStream stream;
	stream.Write((MessageID)GO_CONNECTION);
	stream.Write((MessageID)SERVER_FULL);
	network->GetPeer()->Send(&stream,LOW_PRIORITY,RELIABLE,0,clientAddress,false);
	network->GetPeer()->CloseConnection(clientAddress,true);	
};

void ConnectionRPC::NicknameUsed(CNetwork* network, SystemAddress clientAddress)
{
	BitStream stream;
	stream.Write((MessageID)GO_CONNECTION);
	stream.Write((MessageID)NICKNAME_USED);
	network->GetPeer()->Send(&stream,LOW_PRIORITY,RELIABLE,0,clientAddress,false);
	network->GetPeer()->CloseConnection(clientAddress,true);
};

void ConnectionRPC::ClosedConnectionWithReason(CNetwork* network, SystemAddress clientAddress, RakString reason)
{
	BitStream stream;
	stream.Write((MessageID)GO_CONNECTION);
	stream.Write((MessageID)CLOSED_CONNECTION_REASON);
	stream.Write(reason);

	network->GetPeer()->Send(&stream,LOW_PRIORITY,RELIABLE,0,clientAddress,false);
	network->GetPeer()->CloseConnection(clientAddress,true);
};