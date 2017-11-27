#ifndef CPLAYERMANAGER_H
#define CPLAYERMANAGER_H

#define playerManager CPlayerManager::GetManager()

class CLocalPlayer;
class CPlayer;

class CPlayerManager
{
private:
	CLocalPlayer* pLocalPlayer;

	CPlayerManager();
	CPlayerManager( const CPlayerManager & ){};
	~CPlayerManager();
public:
	List<CPlayer*> playerList;

	static CPlayerManager & GetManager()
	{
		static CPlayerManager manager;
		return manager;
	};

	unsigned int GetNumberOfPlayers()
	{
		return this->playerList.Num();
	}

	CLocalPlayer* CreateLocalPlayer(int playerID, RakString playerName);
	CPlayer* CreatePlayer(int playerID, RakString playerName);
	bool DestroyPlayer(CPlayer* player);
	bool IsPlayerSynchronised(oCNpc* npc); //Czy ten npc jest zsynchronizowany
	void DestroyAllPlayers(); //Sync œwiatów
	//Save'y
	void DestroyAllNpcs();
	void CreateAllNpcs();

	void RepairAllPlayers();

	CPlayer* GetPlayer(int playerID);
	CPlayer* GetPlayer(oCNpc* npc);
	CLocalPlayer* GetLocalPlayer() { return this->pLocalPlayer;};
};

#endif //CPLAYERMANAGER_H