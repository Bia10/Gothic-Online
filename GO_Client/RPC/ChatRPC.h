#ifndef CHATRPC_H
#define CHATRPC_H

namespace ChatRPC
{
	void HandleChatRPC(CNetwork* network, Packet* packet);
	void ServerMessage(CNetwork* network, BitStream& stream);
	void MessageRGB(CNetwork* network, BitStream& stream);
};

#endif //CHATRPC_H