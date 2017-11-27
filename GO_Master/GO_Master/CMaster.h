#pragma once
#include "stdInc.h"

class CMaster
{
private:
	unsigned int listFileTime;
	unsigned int htmlListFileTime;
	unsigned int timeUnactive;
	CNetwork* pNetwork;

	CMaster();
	~CMaster();
	CMaster( const CMaster & ) {};

	vector<CServer*> serverList;
public:
	static CMaster & GetInstance()
	{
		static CMaster m;
		return m;
	}

	void StartUp();
	CNetwork* GetNetwork() { return this->pNetwork;};

	void ReceivePackets();
	void CreateListFile();
	void CreateListFileHTML();
	void ClearUnactive();
};
