#ifndef CSERVER_H
#define CSERVER_H

#define core CServer::GetCore()

struct SMobTrigger
{
	float x, y, z;
	RakString world;

	bool operator==(const SMobTrigger &mob) { if (x == mob.x && y == mob.y && z == mob.z && world == mob.world) return true; return false; }
	SMobTrigger() {}
	SMobTrigger(float _x, float _y, float _z, RakString _world) : x(_x), y(_y), z(_z), world(_world) {}
};

class CServer //singleton
{
private:
	CConfig* pConfig;
	CNetwork* pNetwork;
	CMultiplayer* pMultiplayer;
	CStreamer* pStreamer;
	CBan* pBan;
	CScriptDownload* pScriptDownload;

	RakString serverDescription;
	RakString serverWorld;
	int serverHour, serverMinute, serverDay;
	bool serverUnconscious;

private:
	CServer();
	CServer( const CServer & ) {};
	~CServer();

	void SynchronizeTime();

public:
	List<SMobTrigger> mobList;

	static CServer & GetCore()
	{
		static CServer server;
		return server;
	}

	//Metoda g³ówna (inicjacyjna)
	void Start();
	void MainThread(); //G³ówny w¹tek
	static void SlaveThread(void* arg); //W¹tek niewolniczy

	CConfig* GetConfig() {return this->pConfig;};
	CNetwork* GetNetwork() {return this->pNetwork;};
	CMultiplayer* GetMultiplayer() {return this->pMultiplayer;};
	CStreamer* GetStreamer() {return this->pStreamer;};
	CBan* GetBanSystem() {return this->pBan;};

	inline RakString GetDescription() const {return this->serverDescription;};
	inline RakString GetWorld() const {return this->serverWorld;};
	inline int GetHour() const { return this->serverHour; };
	inline int GetMinute() const { return this->serverMinute; };
	inline int GetDay() const { return this->serverDay; };
	inline bool GetUnconscious() const { return this->serverUnconscious; };
	void SetDescription(RakString _desc) { this->serverDescription = _desc;};
	void SetWorld(RakString _world) { this->serverWorld = _world;};
	void SetUnconscious(bool _enabled);

};

#endif //CSERVER_H