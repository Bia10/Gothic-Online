#ifndef ITEMRPC_H
#define ITEMRPC_H

namespace ItemRPC
{
	void HandleItemRPC(CNetwork* network, Packet* packet);

	void CreateItem(Packet* packet, BitStream& stream);
	void DestroyItem(Packet* packet, BitStream& stream);
};

#endif //ITEMRPC_H