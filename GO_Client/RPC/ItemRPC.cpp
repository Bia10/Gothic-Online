#include "..\\stdafx.h"

void ItemRPC::HandleItemRPC(CNetwork* network, Packet* packet)
{
	BitStream stream(packet->data,packet->length,false);
	stream.IgnoreBytes(1);

	MessageID eItemRPC;
	stream.Read(eItemRPC);
	switch(eItemRPC)
	{
	case CREATE_ITEM: CreateItem(stream); break;
	case DESTROY_ITEM: DestroyItem(stream); break;
	}
};

void ItemRPC::CreateItem(BitStream& stream)
{
	DLOG("ItemRPC::CreateItem()");
	size_t itemID;
	RakString itemInstance;
	size_t amount;
	float x, y, z;
	
	stream.Read(itemID);
	stream.Read(itemInstance);
	stream.Read(amount);
	stream.Read(x);
	stream.Read(y);
	stream.Read(z);

	itemManager.CreateItem(itemInstance, zVEC3(x,y,z), amount, itemID);
};

void ItemRPC::DestroyItem(BitStream& stream)
{
	DLOG("ItemRPC::DestroyItem()");
	size_t itemID;
	stream.Read(itemID);

	itemManager.DestroyItem(itemID);
};