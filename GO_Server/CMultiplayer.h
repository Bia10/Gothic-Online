#ifndef CMULTIPLAYER_H
#define CMULTIPLAYER_H

class CMultiplayer
{
public:
	CMultiplayer();
	~CMultiplayer();

	void CreatePlayerForAllPlayers(CPlayer* player);
	void CreateAllPlayersForPlayer(CPlayer* player);
};

#endif //CMULTIPLAYER_H