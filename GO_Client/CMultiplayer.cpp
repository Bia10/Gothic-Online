#include "stdafx.h"

CMultiplayer::CMultiplayer()
{
	DLOG("CMultiplayer::CMultiplayer()");
	//Zainicjowanie managera
	playerManager;
};

CMultiplayer::~CMultiplayer()
{
	DLOG("CMultiplayer::~CMultiplayer()");
};

bool CMultiplayer::InitMultiplayer(RakString hostname, int myid)
{
	if( this->IsInitiated() == false )
	{
		this->hostName = hostname;
		this->myID = myid;
		this->bInitiated = true;

		return true;
	}

	return false;
};

void CMultiplayer::RepairDoor()
{
	bool next = true;
	while (next && !triggerQueue.empty())
	{
		if (GetTimeMS() > triggerQueue.front().time)
		{
			oCMobInter *mob = triggerQueue.front().mob;
			mob->StopInteraction(triggerQueue.front().npc);
			triggerQueue.pop();
			next = true;
		}
		else
			next = false;
	}
}