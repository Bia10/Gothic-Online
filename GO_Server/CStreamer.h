#ifndef CSTREAMER_H
#define CSTREAMER_H

#define STREAM_TIME 1000
#define ITEM_STREAM_TIME 1000
#define STREAM_DISTANCE 3000

class CStreamer
{
private:
	unsigned int timeStreamPlayers;
	unsigned int timeStreamItems;
public:
	CStreamer();
	~CStreamer();

	void Pulse();
	void StreamPlayers(bool timeout = true);
	void StreamItems();

	bool IsPlayerStreamedToPlayer(CPlayer* p1, CPlayer* p2);
	bool IsItemStreamedToPlayer(CItem* item, CPlayer* player);
};

#endif //CSTREAMER_H