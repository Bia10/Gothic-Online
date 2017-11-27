#include "..\\stdafx.h"

void ConnectionRPC::HandleConnectionRPC(CNetwork* network, Packet* packet)
{
	DLOG("ConnectionRPC::HandleConnectionRPC()");
	BitStream stream(packet->data,packet->length,false);
	stream.IgnoreBytes(1);

	MessageID eConnectionRPC;
	stream.Read(eConnectionRPC);

	switch(eConnectionRPC)
	{
	case ACCEPT_CONNECTION: AcceptConnection(network,stream); break;
	case INCORRECT_VERSION: IncorrectVersion(network); break;
	case SERVER_FULL: ServerFull(network); break;
	case NICKNAME_USED: NicknameUsed(network); break;
	}

};

void ConnectionRPC::CatchConnection(CNetwork* network, Packet* packet)
{
	DLOG("ConnectionRPC::CatchConnection()");
	network->InitServerAddress(packet->systemAddress);
	CConfig* cfg = core.GetConfig();
	zVEC3 pos = oCNpc::GetHero()->GetPosition(); //Hardcoded BITCH

	md5wrapper md5;
	RakString dllHash = md5.getHashFromFile("system//GO.dll").c_str();
	//RakString dllHash("b2b410288ca298f5b7d84c87715e8663");

	BitStream stream;
	stream.Write((MessageID)GO_CONNECTION);
	stream.Write((MessageID)PLEASE_CONNECT);
	stream.Write(versionNumber);
	stream.Write(dllHash);
	stream.Write(cfg->GetPlayerName());
	stream.Write(cfg->GetStartWorld());
	stream.Write(pos.x);
	stream.Write(pos.y);
	stream.Write(pos.z);
	
	network->GetPeer()->Send(&stream,HIGH_PRIORITY,RELIABLE,NULL,network->GetServerAddress(),false);
	network->GetPeer()->Ping(network->GetServerAddress());
#ifdef COOP
	//oCGame::GetGame()->GetSpawnManager()->SetSpawningEnabled(1); //W³¹cza npc
#endif //COOP
	
	
};

void ConnectionRPC::LostConnection(CNetwork* network, Packet* packet)
{
	DLOG("ConnectionRPC::LostConnection()");
	//core.GetChat()->AddLine(RakString("Connection lost"), zCOLOR(255, 0, 0, 255));
	core.GetChat()->AddLine(RakString("Po³¹czenie utracone"), zCOLOR(255, 0, 0, 255));
	network->Disconnect();
};

void ConnectionRPC::Disconnection(CNetwork* network, Packet* packet)
{
	DLOG("ConnectionRPC::Disconnection()");
	//core.GetChat()->AddLine(RakString("Server closed the connection"), zCOLOR(255,0,0,255));
	core.GetChat()->AddLine(RakString("Serwer zamkn¹³ po³¹czenie"), zCOLOR(255,0,0,255));
	network->Disconnect();
};

void ConnectionRPC::AcceptConnection(CNetwork* network, BitStream& stream)
{
	DLOG("ConnectionRPC::AcceptConnection()");
	CMultiplayer* m = core.GetMultiplayer();
	int hour, minute, day;
	bool unconscious;

	stream.Read(m->hostName);
	stream.Read(m->myID);
	stream.Read(hour);
	stream.Read(minute);
	stream.Read(day);
	stream.Read(unconscious);

	// Time sync
	oCGame::GetGame()->SetTime(day, hour, minute);

	// Unconscious
	scr.GetScriptVars()->isUnconsciousEnabled = unconscious;

	//core.GetChat()->AddLine(RakString("Connected to: %s. Joining the game...",m->hostName.C_String()), zCOLOR(0, 230, 255, 255));

	core.GetChat()->AddLine(RakString("Po³¹czono z: %s. Do³¹czanie do gry...",m->hostName.C_String()), zCOLOR(0, 255, 0, 255));

	CConfig* config = core.GetConfig();
	if (scr.StartScript(config->GetClientScript().C_String()))
		DLOG("Script %s has been loaded", config->GetClientScript().C_String());
	else
		DLOG("Cannot load script!");

	network->bConnected = true;
};

void ConnectionRPC::IncorrectVersion(CNetwork* network)
{
	DLOG("ConnectionRPC::IncorrectVersion()");

	//core.GetChat()->AddLine(RakString("Incorrect version"), zCOLOR(255,0,0,255));
	core.GetChat()->AddLine(RakString("Z³a wersja Gothic Online"), zCOLOR(255,0,0,255));
	network->Disconnect();
};

void ConnectionRPC::ServerFull(CNetwork* network)
{
	DLOG("ConnectionRPC::ServerFull()");

	//core.GetChat()->AddLine(RakString("Server is full"), zCOLOR(255,0,0,255));
	core.GetChat()->AddLine(RakString("Serwer jest pe³ny"), zCOLOR(255,0,0,255));
	network->Disconnect();
};

void ConnectionRPC::NicknameUsed(CNetwork* network)
{
	DLOG("ConnectionRPC::NicknameUsed()");

	//core.GetChat()->AddLine(RakString("Nickname is already used"), zCOLOR(255,0,0,255));
	core.GetChat()->AddLine(RakString("Twój nick jest ju¿ zajêty"), zCOLOR(255,0,0,255));
	network->Disconnect();
};

void ConnectionRPC::Banned(CNetwork* network)
{
	DLOG("ConnectionRPC::Banned()");

	//core.GetChat()->AddLine(RakString("You're banned from this server!"), zCOLOR(255,0,0,255));
	core.GetChat()->AddLine(RakString("Masz aktywnego bana na tym serwerze!"), zCOLOR(255,0,0,255));
	network->Disconnect();
};

void ConnectionRPC::DisconnectedWithReason(CNetwork* network, BitStream& stream)
{
	DLOG("ConnectionRPC::DisconnectedWithReason()");

	RakString reason;
	stream.Read(reason);

	core.GetChat()->AddLine(RakString("Disconnected: %s", reason.C_String()), zCOLOR(255,0,0,255));
	network->Disconnect();
};

void ConnectionRPC::ConnectionFailed(CNetwork* network)
{
	DLOG("ConnectionRPC::ConnectionFailed()");

	//core.GetChat()->AddLine(RakString("Can't reach server (connection attempt failed)"), zCOLOR(255,0,0,255));
	core.GetChat()->AddLine(RakString("Nie mo¿na po³¹czyæ z serwerem (próba po³¹czenia nieudana)"), zCOLOR(255,0,0,255));
	network->Disconnect();
};