#ifndef CCONFIG_H
#define CCONFIG_H

class CConfig
{
private:
	RakString playerName;
	RakString serverIp;
	RakString serverPort;
	RakString startWorld;
	RakString playerInstance;
	RakString clientScript;
	RakString language;
public:
	CConfig();
	~CConfig();

	bool LoadConfigFromFile(RakString fileName);
	void SaveConfigToFile(RakString fileName);
	void SetDefault();

	inline RakString GetPlayerName(){ return this->playerName;};
	inline RakString GetServerIp(){ return this->serverIp;};
	inline RakString GetServerPort(){ return this->serverPort;};
	inline RakString GetStartWorld(){ return this->startWorld;};
	inline RakString GetPlayerInstance(){ return this->playerInstance;};
	inline RakString GetClientScript(){ return this->clientScript;};
	inline RakString GetLanguage(){ return this->language; };

};

#endif //CCONFIG_H