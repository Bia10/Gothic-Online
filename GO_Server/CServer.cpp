#include "stdafx.h"

CServer::CServer()
{
	LOG("-== Gothic Online Server %s ==-", versionString);
	//DLOG("CServer::CServer()\n");
	//Inicjacja wszystkich elementów serwer'a
	pConfig = new CConfig();
	pNetwork = new CNetwork();
	pMultiplayer = new CMultiplayer();
	pStreamer = new CStreamer();
	pBan = new CBan();
	pScriptDownload = new CScriptDownload();

	serverDescription = "<font color=orange><b>G</b></font>othic Online <font color=lightgreen><b>S</b></font>erver";
	serverWorld = "WORLD.ZEN";
	serverHour = 8; serverMinute = 0; serverDay = 0;
	serverUnconscious = true;
	mobList.Clear();
};

CServer::~CServer()
{
	//DLOG("CServer::~CServer()\n");

	delete pConfig;
	delete pNetwork;
	delete pMultiplayer;
	delete pStreamer;
	delete pBan;
	delete pScriptDownload;

};

void CServer::Start()
{
	//DLOG("CServer::Start()\n");
	//Informacje o konfiguracji servera
	LOG("[config] Server name: %s", GetConfig()->GetServerName().C_String());
	LOG("[config] Server port: %s", GetConfig()->GetServerPort().C_String());
	LOG("[config] Max slots: %s", GetConfig()->GetMaxSlots().C_String());
	LOG("[config] Client script: %s", GetConfig()->GetClientScript().C_String());
	LOG("[config] Server script: %s", GetConfig()->GetServerScript().C_String());
	LOG("[info] Loading scripts...");
	if( scr.StartScript(pConfig->GetServerScript().C_String()) )
		LOG("[Squirrel] All scripts should be loaded!");
	LOG("[info] Starting network...");

	//Inicjacja sieci
	if( (this->pNetwork->InitNetwork()) == true )
	{
		//Downloader
		pScriptDownload->StartUp();
		//W¹tek niewolniczy (streamer, lista graczy)
		thread slave(CServer::SlaveThread, (void*)NULL);
		slave.detach();
		this->MainThread(); //G³ówny w¹tek odbieraj¹cy pakiety
	}
	else
		LOG("[error] Failed to start network");
};

void CServer::SynchronizeTime()
{
	static int syncTime = GetTimeMS() + 4000;

	if (GetTimeMS() >= syncTime)
	{
		if (++serverMinute > 59)
		{
			serverMinute = 0;
			if (++serverHour > 23)
			{
				serverHour = 0;
				if (++serverDay > 6)
					serverDay = 0;
			}
		}

		syncTime = GetTimeMS() + 4000;
	}
}

/*
	https://www.youtube.com/watch?v=DkaKR0H6klY
	Poletzam
	ma ktoœ poratowaæ fajom?
*/
void CServer::SlaveThread(void *arg)
{
	while( true )
	{
		if (core.GetConfig()->GetServerPublic())
			master.Pulse();

		RakSleep(30);
	}
}

void CServer::MainThread()
{
	//DLOG("CServer::Loop()\n");
	while( true )
	{
		playerManager.BroadcastPlayerList();
		playerManager.CheckPlayersTimedOverlays();
		pStreamer->Pulse();
		SynchronizeTime();
		scr.OnTick();
		pNetwork->GetReceiver()->ReceivePackets(pNetwork);

		RakSleep(1);
	}
};

void CServer::SetUnconscious(bool _enabled)
{
	serverUnconscious = _enabled;

	BitStream bStream;
	bStream.Write((MessageID)GO_SCRIPT);
	bStream.Write((MessageID)SCRIPT_UNCONSCIOUS);
	bStream.Write(serverUnconscious);

	pNetwork->SendToAll(bStream, MEDIUM_PRIORITY, RELIABLE);
}