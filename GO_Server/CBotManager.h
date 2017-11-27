/*
*
*	Project:		Gothic 2 Online
*	License:		License is avaiable in main directory
*	File:			CPlayer.h
*	Destination:	Server | Bot manager
*	Developers:		Sative aka V0ID, Bimbol
*	Website:		http://www.gothic-online.com.pl
*
*/

#ifndef CBOTMANAGER_H
#define CBOTMANAGER_H

#define botManager CBotManager::getManager()
#define botListIter map<int, CNpc*>::iterator

class CNpc;

class CBotManager
{
private:
	map<int, CNpc*> botList;
	CBotManager();
	CBotManager( const CBotManager & ) {};
	~CBotManager();

	size_t getFreeID();
public:
	static CBotManager & getManager()
	{
		static CBotManager manager;
		return manager;
	}

	void pulse();

	CNpc* createNpc( RakString name, RakString instance );
	void destroyNpc( CNpc* bot );
	inline void destroyNpc( size_t id );
	inline CNpc* get( size_t id );
	inline size_t getCount() { return botList.size(); };
};

#endif //CBOTMANAGER_H