#ifndef ITEMRPC_H
#define ITEMRPC_H

namespace ItemRPC
{
	void HandleItemRPC(CNetwork* network, Packet* packet);

	void CreateItem(BitStream& stream);
	void DestroyItem(BitStream& stream);
};

#endif //ITEMRPC_H