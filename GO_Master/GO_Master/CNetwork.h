#pragma once
class CNetwork
{
private:
	RakPeerInterface* peer;
public:
	CNetwork();
	~CNetwork();

	RakPeerInterface* GetPeer() {return this->peer;};
	bool Init();
};