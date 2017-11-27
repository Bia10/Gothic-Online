#ifndef CMASTER_H
#define CMASTER_H

#define master CMaster::GetInstance()

class CMaster
{
private:
	RakPeerInterface* peer;
	unsigned int timeRefreshMaster;
	bool isConnected;

	CMaster();
	CMaster(const CMaster&) {};
	~CMaster();
public:
	static CMaster & GetInstance()
	{
		static CMaster m;
		return m;
	}

	void Pulse();
};

#endif CMASTER_H