#ifndef CNETWORK_H
#define CNETWORK_H

class CNetwork
{
private:
	bool bIsInitiated;
	RakPeerInterface* peer;
	SystemAddress serverAddress;
	CReceiver* pReceiver;
public:
	bool bConnected;

	CNetwork();
	~CNetwork();

	bool IsConnected() const{ return this->bConnected;};
	bool IsInitiated() const{ return this->bIsInitiated;};
	RakPeerInterface* GetPeer() const{ return this->peer;};
	SystemAddress GetServerAddress() const{ return this->serverAddress;};

	bool InitNetwork();
	void InitServerAddress(SystemAddress address) {this->serverAddress = address;};
	void Connect(RakString address, unsigned short port);
	void Disconnect();

	CReceiver* GetReceiver() { return this->pReceiver;};
};

#endif //CNETWORK_H