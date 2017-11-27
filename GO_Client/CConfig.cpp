#include "stdafx.h"

CConfig::CConfig()
{
	DLOG("CConfig::CConfig()");

	if(LoadConfigFromFile("..\\Multiplayer\\GO_Config.client.xml") == false)
	{
		if(LoadConfigFromFile("Multiplayer\\GO_Config.client.xml") == false)
		{
			SetDefault();
			SaveConfigToFile("..\\Multiplayer\\GO_Config.client.xml");
		}
	}

};

CConfig::~CConfig()
{
	DLOG("CConfig::~CConfig()");
};

bool CConfig::LoadConfigFromFile(RakString fileName)
{
	DLOG("CConfig::LoadConfigFromFile(%s)", fileName.C_String());

	TiXmlElement* pElement = NULL;
	TiXmlDocument document(fileName.C_String());
	if(document.LoadFile())
	{
		DLOG("Config file found");
		TiXmlElement* root = document.FirstChildElement( "GO_Config" );
		char buff[256];
		pElement = root->FirstChildElement( "playerName" );
		if( pElement )
		{
			sprintf(buff, "%s\0", pElement->GetText());
			this->playerName = buff;
			memset(buff, 0, sizeof(buff));
		}
		pElement = root->FirstChildElement( "serverIp" );
		if( pElement )
		{
			sprintf(buff, "%s\0", pElement->GetText());
			this->serverIp = buff;
			memset(buff, 0, sizeof(buff));
		}
		pElement = root->FirstChildElement( "serverPort" );
		if( pElement )
		{
			sprintf(buff, "%s\0", pElement->GetText());
			this->serverPort = buff;
			memset(buff, 0, sizeof(buff));
		}
		pElement = root->FirstChildElement( "startWorld" );
		if( pElement )
		{
			sprintf(buff, "%s\0", pElement->GetText());
			this->startWorld = buff;
			memset(buff, 0, sizeof(buff));
		}
		pElement = root->FirstChildElement( "playerInstance" );
		if( pElement )
		{
			sprintf(buff, "%s\0", pElement->GetText());
			this->playerInstance = buff;
			memset(buff, 0, sizeof(buff));
		}
		pElement = root->FirstChildElement( "clientScript" );
		if( pElement )
		{
			sprintf(buff, "%s\0", pElement->GetText());
			this->clientScript = buff;
			memset(buff, 0, sizeof(buff));
		}
		pElement = root->FirstChildElement( "lang" );
		if (pElement)
		{
			sprintf(buff, "%s\0", pElement->GetText());
			this->language = buff;
			memset(buff, 0, sizeof(buff));
		}
		return true;
	}
	DLOG("Config file doesn't exist");
	return false;
};

void CConfig::SaveConfigToFile(RakString fileName)
{
	DLOG("CConfig::SaveConfigToFile(%s)", fileName.C_String());
	FILE* config = fopen(fileName.C_String(), "w");
	fprintf(config, "<!-- Gothic Online automatic generated config file -->\n");
	fprintf(config, "<GO_Config>\n");
	fprintf(config, "	<playerName>%s</playerName>\n", this->playerName.C_String());
	fprintf(config, "	<serverIp>%s</serverIp>\n", this->serverIp.C_String());
	fprintf(config, "	<serverPort>%s</serverPort>\n", this->serverPort.C_String());
	fprintf(config, "	<startWorld>%s</startWorld>\n", this->startWorld.C_String());
	fprintf(config, "	<playerInstance>%s</playerInstance>\n", this->playerInstance.C_String());
	fprintf(config, "	<clientScript>%s</clientScript>\n", this->clientScript.C_String());
	fprintf(config, "</GO_Config>\n");
	fclose(config);
};

void CConfig::SetDefault()
{
	DLOG("CConfig::SetDefault()");

	this -> playerName = "Nickname";
	this -> serverIp = "127.0.0.1";
	this -> serverPort = "28970";
	this -> startWorld = "WORLD.ZEN";
	this -> playerInstance = "PC_HERO";
	this -> clientScript = "client-main.gm";
};