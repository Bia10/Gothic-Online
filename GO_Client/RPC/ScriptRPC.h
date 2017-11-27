#ifndef SCRIPTRPC_H
#define SCRIPTRPC_H

namespace ScriptRPC
{
	void HandleScriptRPC(CNetwork* network, Packet* packet);

	void ScriptLoad(CNetwork* network, BitStream& stream);
	void ScriptPacket(CNetwork* network, BitStream& stream);
	void ScriptUnconscious(CNetwork* network, BitStream& stream);
	void ScriptVisual(CNetwork* network, BitStream& stream);
	void ScriptCall(CNetwork* network, BitStream& stream);
	void ScriptCheck(CNetwork* network, BitStream& stream);
};

#endif //SCRIPTRPC_H