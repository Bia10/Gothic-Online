#ifndef SCRIPTRPC_H
#define SCRIPTRPC_H

namespace ScriptRPC
{
	void HandleScriptRPC(CNetwork* network, Packet* packet);

	void ScriptPacket(CNetwork* network, BitStream& stream, Packet* packet);
	void ScriptVisual(CNetwork* network, BitStream& stream, Packet* packet);
	void ScriptCall(CNetwork* network, BitStream& stream, Packet* packet);
	void ScriptFocus(CNetwork* network, BitStream& stream, Packet* packet);
};

#endif //SCRIPTRPC_H