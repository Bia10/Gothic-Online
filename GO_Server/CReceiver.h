#ifndef CRECEIVER_H
#define CRECEIVER_H

class CNetwork; //Bo tutaj oczywi�cie nie ma dost�pu do tej klasy

class CReceiver
{
public:
	CReceiver();
	~CReceiver();

	void ReceivePackets(CNetwork* network);
};

#endif //CRECIEVER_H