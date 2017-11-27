#ifndef CPLAYERLIST_H
#define CPLAYERLIST_H

class CPlayerList
{
private:
	RakString* playerList;
	zCView* texture;
	bool isShowing;
	//Singletone
	CPlayerList( const CPlayerList& ) {};
	CPlayerList();
	~CPlayerList();
public:
	static CPlayerList & GetInstance()
	{
		static CPlayerList pList;
		return pList;
	}

	void Render();
	RakString* GetList(){ return this->playerList; };
};


#endif //CPLAYERLIST_H