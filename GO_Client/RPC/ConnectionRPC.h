#ifndef CONNECTIONRPC_H
#define CONNECTIONRPC_H

namespace ConnectionRPC
{
	void HandleConnectionRPC(CNetwork* network, Packet* packet);
	void CatchConnection(CNetwork* network, Packet* packet);
	void LostConnection(CNetwork* network, Packet* packet);
	void Disconnection(CNetwork* network, Packet* packet);

	void AcceptConnection(CNetwork* network, BitStream& stream);
	void IncorrectVersion(CNetwork* network);
	void ServerFull(CNetwork* network);
	void NicknameUsed(CNetwork* network);
	void DisconnectedWithReason(CNetwork* network, BitStream& stream);
	void ConnectionFailed(CNetwork* network);
	void Banned(CNetwork* network);
};

#endif //CONNECTIONRPC_H