#ifndef CPLAYER_H
#define CPLAYER_H

struct STimedOverlay
{
	TimeMS time;
	RakString overlay;

	STimedOverlay() {}
	STimedOverlay(TimeMS _time, RakString _overlay) : time(_time), overlay(_overlay) {}
};

class CPlayer : public CCreature
{
public:
	SystemAddress addr; //player addr
	int playerId;
public:
	List<CPlayer*> streamedPlayers;
	List<CItem*> streamedItems;
	List<RakString> overlaysList;
	List<STimedOverlay> timedOverlays;
	bool bConnected;

	CPlayer(SystemAddress _clientAddress, int _playerID, RakString _playerName);
	~CPlayer();

	void Disconnect();
	void CheckTimedOverlay();

	inline SystemAddress GetAddress(){return this->addr;};
	inline const char* GetIP() {return inet_ntoa(this->addr.address.addr4.sin_addr);};
	inline int GetID() { return this->playerId;};
	inline int GetVirutalWorld() { return this->virtualWorld; };
	void SetVirtualWorld(unsigned world_id) { this->virtualWorld = world_id; };
};

#endif //CPLAYER_H