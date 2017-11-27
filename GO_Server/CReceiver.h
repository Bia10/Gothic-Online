#ifndef CRECEIVER_H
#define CRECEIVER_H

class CNetwork; //Bo tutaj oczywiœcie nie ma dostêpu do tej klasy

class CReceiver
{
public:
	CReceiver();
	~CReceiver();

	void ReceivePackets(CNetwork* network);
};

#endif //CRECIEVER_H