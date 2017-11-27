#include "stdafx.h"

CConfig::CConfig() :
	serverPublic(false)
{
	//DLOG("CConfig::CConfig()\n");
	if(LoadConfigFromFile("GO_Config.server.xml") == false)
	{
		SetDefault();
		SaveConfigToFile("GO_Config.server.xml");
	}

};

CConfig::~CConfig()
{
	//DLOG("CConfig::~CConfig()\n");
};

bool CConfig::LoadConfigFromFile(RakString fileName)
{
	//DLOG("CConfig::LoadConfigFromFile(%s)\n", fileName.C_String());

	TiXmlElement* pElement = NULL;
	TiXmlDocument document(fileName.C_String());
	if(document.LoadFile())
	{
		LOG("[info] Config file found");
		TiXmlElement* root = document.FirstChildElement( "GO_Config" );
		char buff[256];
		pElement = root->FirstChildElement("public");
		if (pElement)
		{
			sprintf(buff, "%s\0", pElement->GetText());
			this->serverPublic = atoi(buff);
			memset(buff, 0, sizeof(buff));
		}
		pElement = root->FirstChildElement( "serverName" );
		if( pElement )
		{
			sprintf(buff, "%s\0", pElement->GetText());
			this->serverName = buff;
			memset(buff, 0, sizeof(buff));
		}
		pElement = root->FirstChildElement( "serverPort" );
		if( pElement )
		{
			sprintf(buff, "%s\0", pElement->GetText());
			this->serverPort = buff;
			memset(buff, 0, sizeof(buff));
		}
		pElement = root->FirstChildElement( "maxSlots" );
		if( pElement )
		{
			sprintf(buff, "%s\0", pElement->GetText());
			this->maxSlots = buff;
			memset(buff, 0, sizeof(buff));
		}
		pElement = root->FirstChildElement( "adminPassword" );
		if( pElement )
		{
			sprintf(buff, "%s\0", pElement->GetText());
			this->adminPassword = buff;
			memset(buff, 0, sizeof(buff));
		};
		pElement = root->FirstChildElement( "serverScript" );
		if( pElement )
		{
			sprintf(buff, "%s\0", pElement->GetText());
			this->serverScript = buff;
			memset(buff, 0, sizeof(buff));
		}
		pElement = root->FirstChildElement( "clientScript" );
		if( pElement )
		{
			sprintf(buff, "%s\0", pElement->GetText());
			this->clientScript = buff;
			memset(buff, 0, sizeof(buff));
		}
		return true;
	}
	LOG("[error] Config file doesn't exist\n");
	return false;
};

void CConfig::SaveConfigToFile(RakString fileName)
{
	//DLOG("CConfig::SaveConfigToFile(%s)\n", fileName.C_String());
	FILE* config = fopen(fileName.C_String(), "w");
	fprintf(config, "<!-- Gothic Online automatic generated config file -->\n");
	fprintf(config, "<GO_Config>\n");
	fprintf(config, "	<serverName>%s</serverName>\n", this->serverName.C_String());
	fprintf(config, "	<serverPort>%s</serverPort>\n", this->serverPort.C_String());
	fprintf(config, "	<maxSlots>%s</maxSlots>\n", this->maxSlots.C_String());
	fprintf(config, "	<adminPassword>%s</adminPassword>\n", this->adminPassword.C_String());
	fprintf(config, "	<serverScript>%s</serverScript>\n", this->serverScript.C_String());
	fprintf(config, "	<clientScript>%s</clientScript>\n", this->clientScript.C_String());
	fprintf(config, "</GO_Config>\n");
	fclose(config);
};

void CConfig::SetDefault()
{
	//DLOG("CConfig::SetDefault()\n");

	this -> serverName = "Default server name";
	this -> serverPort = "28970";
	this -> maxSlots = "32";
	this -> adminPassword = "password";
	this -> serverScript = "server-main.gm";
	this -> clientScript = "client-main.gm";
};