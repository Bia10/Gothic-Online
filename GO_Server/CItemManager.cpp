#include "stdafx.h"

CItemManager::CItemManager()
{
	itemList.Clear();
};

CItemManager::~CItemManager()
{
	itemList.Clear();
};

bool CItemManager::GetFreeID(unsigned int& itemID)
{
	if( GetNumberOfItems() > 0 )
	{
		for( unsigned int i = 0; ; ++i )
		{
			for( unsigned int j = 0; ; ++j )
			{
				if( i == itemList[j]->GetID() )
					break;
				else if( j == GetNumberOfItems() - 1 && i != itemList[j]->GetID() )
				{
					itemID = i;
					return true;
				}
			}
		}
	}
	else
	{
		itemID = 0;
		return true;
	}
	return false;
};

CItem* CItemManager::GetItem(unsigned int _itemID)
{
	if( GetNumberOfItems() > 0 )
	{ 
		for( unsigned int i = 0; i < GetNumberOfItems() ; ++i )
		{
			if( itemList[i]->GetID() == _itemID )
				return itemList[i];
		}
	}
	return NULL;
};

CItem* CItemManager::CreateItem(RakString instance, unsigned int amount, float x, float y, float z, RakString world)
{
	LOG("Creating item %s amount %d at pos %f %f %f", instance.C_String(), amount, x, y, z);
	unsigned int itemID;
	if( GetFreeID(itemID) == true )
	{
		CItem* item = new CItem(instance,amount,x,y,z,itemID,world);
		if( item )
		{
			itemList.PushBack(item);
			return item;
		}
	}
	return NULL;
};

bool CItemManager::DestroyItem(unsigned int _itemID)
{
	CItem* item = GetItem(_itemID);
	if( item )
	{
		LOG("Destroying item instance %s id %d", item->GetInstance().C_String(), item->GetID());
		itemList.Remove(item);
		//Usuniêcie ze streamera
		for( playerListIter i = playerManager.playerList.begin(); i != playerManager.playerList.end(); ++i )
			DestroyItemForPlayer(item, i->second);
		delete item;
		return true;
	}
	return false;
};

bool CItemManager::CreateItemForPlayer(CItem* item, CPlayer *player)
{
	if( item && player )
	{
		if( player->streamedItems.FindIndex(item) == -1 )
		{
			LOG("Creating item %d for player %s", item->GetID(), player->name.C_String());
			float x,y,z;
			item->GetPositionXYZ(x,y,z);

			BitStream stream;
			stream.Write((MessageID)GO_ITEM);
			stream.Write((MessageID)CREATE_ITEM);
			stream.Write(item->GetID());
			stream.Write(item->GetInstance());
			stream.Write(item->GetAmount());
			stream.Write(x);
			stream.Write(y);
			stream.Write(z);
			
			player->streamedItems.PushBack(item);

			CNetwork* net = core.GetNetwork();
			if( net->GetPeer()->Send(&stream,LOW_PRIORITY,RELIABLE,0,player->GetAddress(),false) )
				return true;
		}
	}
	return false;
};

bool CItemManager::DestroyItemForPlayer(CItem* item, CPlayer *player)
{
	if( item && player )
	{
		int index = player->streamedItems.FindIndex(item);
		if( index != -1 )
		{
			LOG("Destroying item %d for player %d", item->GetID(), player->name.C_String());
			BitStream stream;
			stream.Write((MessageID)GO_ITEM);
			stream.Write((MessageID)DESTROY_ITEM);
			stream.Write(item->GetID());

			player->streamedItems.RemoveIndex(index);

			CNetwork* net = core.GetNetwork();
			if( net->GetPeer()->Send(&stream,LOW_PRIORITY,RELIABLE,0,player->GetAddress(),false) )
				return true;
		}
	}
	return false;
};