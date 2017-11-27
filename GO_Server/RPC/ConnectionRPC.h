#ifndef CONNECTIONRPC_H
#define CONNECTIONRPC_H

namespace ConnectionRPC
{
	void HandleConnectionRPC(CNetwork* network, Packet* packet);
	void CatchConnection(CNetwork* network, Packet* packet);
	void LostConnection(CNetwork* network, Packet* packet);
	void Disconnection(CNetwork* network, Packet* packet);
	void PleaseConnect(CNetwork* network, BitStream& stream, SystemAddress clientAddress);

	//Send
	void IncorrectVersion(CNetwork* network, SystemAddress clientAddress);
	void ServerFull(CNetwork* network, SystemAddress clientAddress);
	void NicknameUsed(CNetwork* network, SystemAddress clientAddress);
	void ClosedConnectionWithReason(CNetwork* network, SystemAddress clientAddress, RakString reason);
};

#endif //CONNECTIONRPC_H