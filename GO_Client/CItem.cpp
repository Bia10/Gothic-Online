#include "stdafx.h"

CItem::CItem(RakString _instanceName, oCItem *_gameItem, size_t _amount, zVEC3 _pos, size_t _id)
{
	id = _id;
	instanceName = _instanceName;
	gameItem = _gameItem;
	amount = _amount;
	pos = _pos;
};

CItem::~CItem()
{
	instanceName.FreeMemory();
	if( gameItem )
		if(!oCNpc::GetHero()->IsInInv(gameItem))
			gameItem->RemoveVobFromWorld();
};