#pragma once
class CServer
{
public:
	RakString address;
	unsigned int port;
	RakString hostName;
	unsigned int playersOnline;
	unsigned int maxSlots;
	RakString description;
	RakString clientScript;
	RakString versionString;
	RakString world;

	unsigned int lastUpdated;
};
