#ifndef CPLAYERMANAGER_H
#define CPLAYERMANAGER_H

#define playerManager CPlayerManager::GetManager()
#define playerListIter map<int,CPlayer*>::iterator
class CPlayer;

#ifndef INLINE
	#ifdef _MSC_VER
		#define INLINE __forceinline
	#else
		#define INLINE inline __attribute__((always_inline))
	#endif
#endif

class CPlayerManager
{
private:
	unsigned int timerBroadcastList;

	CPlayerManager();
	CPlayerManager( const CPlayerManager & ){};
	~CPlayerManager();
public:
	map<int, CPlayer*> playerList;

	static CPlayerManager & GetManager()
	{
		static CPlayerManager manager;
		return manager;
	};

	bool IsNicknameUsed(RakString playerName);
	bool IsPlayerInManager(CPlayer* player);

	CPlayer* CreatePlayer(SystemAddress address, RakString playerName);
	void CreatePlayerForOtherPlayer(CPlayer* player, CPlayer* receiver); //synchronizowanie graczy
	bool DestroyPlayer(CPlayer* player);
	void CheckPlayersTimedOverlays();

	CPlayer* GetPlayer(int playerID);
	CPlayer* GetPlayer(SystemAddress clientAddress);
	CPlayer* GetPlayer(RakString playerName);

	unsigned int GetNumberOfPlayers()
	{
		return this->playerList.size();
	}

	void BroadcastPlayerList();
};


#endif //CPLAYERMANAGER_H