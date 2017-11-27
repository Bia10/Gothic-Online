#include "../stdafx.h"

void ItemRPC::HandleItemRPC(CNetwork* network, Packet* packet)
{
	BitStream stream(packet->data,packet->length,false);
	stream.IgnoreBytes(1);

	MessageID eItemRPC;
	stream.Read(eItemRPC);
	switch(eItemRPC)
	{
	case CREATE_ITEM: CreateItem(packet,stream); break;
	case DESTROY_ITEM: DestroyItem(packet,stream); break;
	}
};

void ItemRPC::CreateItem(Packet* packet, BitStream& stream)
{
	RakString instanceName;
	unsigned int amount;
	float x, y, z;
	RakString world;

	stream.Read(instanceName);
	stream.Read(amount);
	stream.Read(x);
	stream.Read(y);
	stream.Read(z);
	stream.Read(world);

	CItem* item = itemManager.CreateItem(instanceName,amount,x,y,z,world);
	if( item )
		SCallback::onDrop(playerManager.GetPlayer(packet->systemAddress)->GetID(), item->GetID(), instanceName.C_String(), amount, world.C_String());
};

void ItemRPC::DestroyItem(Packet* packet, BitStream& stream)
{
	unsigned int itemID;
	stream.Read(itemID);
	CItem* item = itemManager.GetItem(itemID);
	if( item )
		SCallback::onTake(playerManager.GetPlayer(packet->systemAddress)->GetID(), item->GetID(), item->GetInstance().C_String(), item->GetAmount(), item->GetWorldName().C_String());
	itemManager.DestroyItem(itemID);
};