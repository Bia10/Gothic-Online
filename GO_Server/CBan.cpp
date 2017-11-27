#include "stdafx.h"

CBan::CBan()
{
	banList.Clear();
};

CBan::~CBan()
{
	banList.Clear();
};

bool CBan::PushToBanList(RakString address)
{
	for( size_t i = 0; i < banList.Num(); i++ )
	{
		if( address.StrCmp(RakString(banList[i])) == 0 )
		{
			return false;
		}
	}
	CNetwork* net = core.GetNetwork();
	net->GetPeer()->AddToBanList(address.C_String());
	banList.PushBack(address.C_String());
	address.FreeMemory(); //Tutaj raczej zbêdne
	return true;
};

bool CBan::PopFromBanList(RakString address)
{
	for( size_t i = 0; i < banList.Num(); i++ )
	{
		if( address.StrCmp(RakString(banList[i])) == 0 )
		{
			CNetwork* net = core.GetNetwork();
			net->GetPeer()->RemoveFromBanList(banList[i]);
			banList.RemoveIndex(i);
			return true;
		}
	}
	return false;
}

bool CBan::LoadBanList(RakString fileName)
{
	FILE* f = fopen(fileName.C_String(), "r");
	if( f )
	{
		char buff[20];
		while( fgets(buff, 20, f) != NULL )
		{
			LOG("Banlist.go: %s\n", &buff[0]);
			PushToBanList(RakString(buff));
		}
		fclose(f);
		return true;
	}
	return false;
};

bool CBan::SaveBanList(RakString fileName)
{
	FILE* f = fopen(fileName.C_String(), "w+");
	if( f )
	{
		for( size_t i = 0; i < banList.Num(); i++ )
		{
			LOG("Banlist.go: %s\n", banList[i]);
			fputs(banList[i], f);
		}
		fclose(f);
		return true;
	}
	return false;
};

bool CBan::BanPlayer(CPlayer* player, RakString fileName)
{
	if( player && fileName.IsEmpty() == false )
	{
		char ip[20];
		player->GetAddress().ToString(false,&ip[0]);
		if( PushToBanList(RakString(ip)) == true )
		{
			player->Disconnect();
			if( SaveBanList(fileName) == true)
				return true;
		}
	}
	return false;
};