#ifndef CMULTIPLAYER_H
#define CMULTIPLAYER_H

struct STriggerSync
{
	unsigned int time;
	oCNpc *npc;
	oCMobInter *mob;

	STriggerSync(int _time, oCNpc *_npc, oCMobInter *_mob) : time(_time), npc(_npc), mob(_mob) {}
};

class CMultiplayer
{
private:
	bool bInitiated;
public:
	std::queue<STriggerSync> triggerQueue;
	RakString hostName;
	int myID;

	CMultiplayer();
	~CMultiplayer();

	int GetMyID() const{ return this->myID;};
	bool IsInitiated() const{ return this->bInitiated;};
	bool InitMultiplayer(RakString hostname, int myid);
	void RepairDoor();
};

#endif //CMULTIPLAYER_H