#ifndef CRECEIVER_H
#define CRECEIVER_H

class CNetwork;

class CReceiver
{
public:
	CReceiver();
	~CReceiver();

	void ReceivePackets(CNetwork* network);
};

#endif //CRECEIVER