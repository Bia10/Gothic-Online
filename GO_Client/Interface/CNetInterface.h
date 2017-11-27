#ifndef CNETINTERFACE_H
#define CNETINTERFACE_H

#define windowMaxPosX 3250
#define windowMaxPosY 2250

class CNetInterface
{
private:
	//varibles
	bool isShowing;
	unsigned int receivedPacketCount;
	zCView* window;

	//singletone
	CNetInterface();
	CNetInterface( const CNetInterface& ) {};
	~CNetInterface();
public:
	static CNetInterface & GetInstance()
	{
		static CNetInterface netgui;
		return netgui;
	}
	void PushOnePacketCnt(){this->receivedPacketCount++;};
	void Render();
};

#endif //CNETINTERFACE_H