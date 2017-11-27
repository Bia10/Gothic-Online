#include "stdInc.h"

CMaster::CMaster()
{
	serverList.clear();

	listFileTime = 0;
	htmlListFileTime = 0;
	timeUnactive = 0;

	pNetwork = new CNetwork();
};

CMaster::~CMaster()
{
	serverList.clear();

	delete pNetwork;
};

void CMaster::StartUp()
{
	printf("[info] Gothic Online Master Server is starting up!\n");
	if( GetNetwork()->Init() == true )
		ReceivePackets();
};

void CMaster::CreateListFile()
{
	if( listFileTime < GetTimeMS() )
	{
		if( serverList.size() > 0 )
		{
			printf("[info] Generating server list file...\n");
			FILE* file = fopen("list.txt", "w");
			if( file != NULL )
			{
				for( unsigned int i = 0; i < serverList.size(); ++i )
				{
					CServer* s = serverList[i];
					fprintf(file,"%s_%d_%s_%d_%d_%s_%s_%s_%s\n", s->address.C_String(), s->port, s->hostName.C_String(), s->playersOnline, s->maxSlots, s->description.C_String(), s->clientScript.C_String(), s->versionString.C_String(), s->world.C_String());
				}
				fclose(file);
			}
			else printf("[error] Cannot create list file, unknown error\n");
		}
		else printf("[error] Cannot create list file, no servers connected to master\n");
		listFileTime = GetTimeMS() + 10000;
	}
};

void CMaster::CreateListFileHTML()
{
	if( htmlListFileTime < GetTimeMS() )
	{
		FILE* file = fopen("list.html", "w");
		if( file != NULL )
		{
			fprintf(file,"<html>\n");
			fprintf(file,"<head>\n");
			fprintf(file,"	<meta charset=\"UTF-8\" />\n");
			fprintf(file,"</head>\n");
			fprintf(file,"<center>\n");
			fprintf(file,"<table border=\"1\">\n");
			fprintf(file,"	<tr>\n <td>Nazwa serwera: </td><td>IP_PORT: </td><td>Liczba graczy: </td><td>Opis serwera: </td><td>Wersja: </td>\n</tr>\n");
			for( unsigned int i = 0; i < serverList.size(); ++i )
			{
				CServer* s = serverList[i];
				fprintf(file,"	<tr>\n <td>%s</td><td>%s_%d</td><td>%d/%d</td><td>%s</td><td>%s</td>\n </tr>\n", s->hostName.C_String(), s->address.C_String(), s->port, s->playersOnline, s->maxSlots, s->description.C_String(), s->versionString.C_String() );
			}
			fprintf(file,"</table>\n");
			fprintf(file,"</center>\n");
			fprintf(file,"</html>\n");
			fclose(file);

		}
		htmlListFileTime = GetTimeMS() + 10000;
	}
};

void CMaster::ClearUnactive()
{
    if( timeUnactive < GetTimeMS() )
    {
        for(unsigned int i = 0; i < serverList.size(); ++i)
        {
            CServer* srv = serverList[i];
            if( srv->lastUpdated < GetTimeMS() )
            {
                printf("[info] Server %s:%d has been removed from list for unactivity\n", srv->address.C_String(), srv->port);
                serverList.erase(serverList.begin() + i);
                delete srv;
            }
        }
        timeUnactive = GetTimeMS() + 3000;
    }
};

void CMaster::ReceivePackets()
{
	printf("[info] Waiting for servers..\n");
	RakPeerInterface* peer = GetNetwork()->GetPeer();
	while( peer )
	{
		for(Packet* packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive())
		{
			char address[30];
			memset(&address, 0, 30);
			packet->systemAddress.ToString_Old(false,&address[0]);
			printf("[info] Data received from %s\n", address);
			if( packet->data[0] == GO_MASTER )
			{
				BitStream s(packet->data, packet->length, false);
				s.IgnoreBytes(1);
				CServer* srv = new CServer();
				srv->address = address;
				s.Read(srv->port);
				s.Read(srv->hostName);
				s.Read(srv->playersOnline);
				s.Read(srv->maxSlots);
				s.Read(srv->description);
				s.Read(srv->clientScript);
				s.Read(srv->versionString);
				s.Read(srv->world);
				srv->lastUpdated = GetTimeMS() + 180000;
				for(unsigned int i = 0; i < serverList.size(); ++i)
				{
					CServer* srv2 = serverList[i];
					if(srv2->address.StrCmp(srv->address) == 0 && srv2->port == srv->port)
					{
						serverList.erase(serverList.begin() + i);
						delete srv2;
						break;
					}
				}
				printf("[info] Server has been added/updated to the list\n");
				serverList.push_back(srv);
				peer->CloseConnection(packet->systemAddress,false);
			}
		}
		RakSleep(3);
		ClearUnactive();
		CreateListFile();
		CreateListFileHTML();
	}
};
