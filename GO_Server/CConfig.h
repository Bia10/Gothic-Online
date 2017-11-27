#ifndef CCONFIG_H
#define CCONFIG_H

class CConfig
{
private:
	bool serverPublic;
	RakString serverName;
	RakString serverPort;
	RakString maxSlots;
	RakString adminPassword;
	RakString serverScript;
	RakString clientScript;
public:
	CConfig();
	~CConfig();

	bool LoadConfigFromFile(RakString fileName);
	void SaveConfigToFile(RakString fileName);
	void SetDefault();

	inline bool GetServerPublic()		{ return this->serverPublic; };
	inline RakString GetServerName()	{ return this->serverName; };
	inline RakString GetServerPort()	{ return this->serverPort; };
	inline RakString GetMaxSlots()		{ return this->maxSlots; };
	inline RakString GetAdminPassword()	{ return this->adminPassword; };
	inline RakString GetServerScript()	{ return this->serverScript; };
	inline RakString GetClientScript()	{ return this->clientScript; };
};

#endif //CCONFIG_H