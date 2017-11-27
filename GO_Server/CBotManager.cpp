#include "stdafx.h"

CBotManager::CBotManager()
{
	botList.clear();
};

CBotManager::~CBotManager()
{
};

void CBotManager::pulse() //Jakieœ AI botów czy cuœ
{

};

CNpc* CBotManager::get(size_t id)
{
	CNpc* bot = 0;
	if( botList.find(id) != botList.end() )
		bot = botList[id];
	return bot;
};

size_t CBotManager::getFreeID()
{
	size_t id = atoi(core.GetConfig()->GetMaxSlots().C_String()) + 1;
	if( getCount() > 0 )
	{
		for( ; ; ++id )
			if( botList.find(id) == botList.end() )	//Nie istnieje bot o takim id
				return id;
	}
	return id;
};

CNpc* CBotManager::createNpc(RakString name, RakString instance)
{
	size_t id = getFreeID();
	CNpc* bot = new CNpc();
	bot->id = id;
	bot->instance = instance;
	bot->name = name;
	bot->spawned = true;
	botList[id] = bot;
	return bot;
};	//Resztê zrobi streamer

void CBotManager::destroyNpc(CNpc *bot)
{
	botList.erase(bot->id);
	//Pakiet o usuniêciu npc, czyli wymusiæ usuniêcie go ze streamera wszystkim graczom	
	delete bot;
};

void CBotManager::destroyNpc(size_t id)
{
	CNpc* bot = get(id);
	if( bot != NULL )
		return destroyNpc(bot);
};