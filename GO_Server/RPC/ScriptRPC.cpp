#include "../stdafx.h"

void ScriptRPC::HandleScriptRPC(CNetwork* network, Packet* packet)
{
	//LOG("ScriptRPC::HandleScriptRPC()");
	BitStream stream(packet->data,packet->length,false);
	stream.IgnoreBytes(1);

	MessageID eScriptRPC;
	stream.Read(eScriptRPC);

	switch (eScriptRPC)
	{
	case SCRIPT_PACKET:
		ScriptPacket(network, stream, packet); break;
	case SCRIPT_VISUAL:
		ScriptVisual(network, stream, packet); break;
	case SCRIPT_CALL:
		ScriptCall(network, stream, packet); break;
	case SCRIPT_FOCUS:
		ScriptFocus(network, stream, packet); break;
	}
};

void ScriptRPC::ScriptPacket(CNetwork* network, BitStream& stream, Packet* packet)
{
	//LOG("ScriptRPC::ScriptPacket()");
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);
	if( player )
	{
		RakString data;
		stream.Read(data);
		SCallback::onPacket(player->GetID(), data.C_String());
	}
};

void ScriptRPC::ScriptVisual(CNetwork* network, BitStream& stream, Packet* packet)
{
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);
	if (player)
	{
		stream.Read(player->bodyModel);
		stream.Read(player->bodyTexture);
		stream.Read(player->headModel);
		stream.Read(player->headTexture);

		BitStream s;
		s.Write((MessageID)GO_SCRIPT);
		s.Write((MessageID)SCRIPT_VISUAL);
		s.Write(player->GetID());
		s.Write(player->bodyModel);
		s.Write(player->bodyTexture);
		s.Write(player->headModel);
		s.Write(player->headTexture);

		network->SendToPlayersOnList(s, LOW_PRIORITY, RELIABLE_ORDERED, &player->streamedPlayers);
	}
};

void ScriptRPC::ScriptCall(CNetwork* network, BitStream& stream, Packet* packet)
{
	RakString functionCall, format;

	stream.Read(functionCall);
	stream.Read(format);

	int p1; float p2; RakString p3;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, functionCall.C_String());

	unsigned paramSize = format.GetLength() - 1;
	for (int i = 1; i <= paramSize; ++i)
	{
		switch ((format.C_String())[i])
		{
		case 'd':
			stream.Read(p1);
			sq_pushinteger(vm, p1);
			break;
		case 'f':
			stream.Read(p2);
			sq_pushfloat(vm, p2);
			break;
		case 's':
			stream.Read(p3);
			sq_pushstring(vm, p3.C_String(), -1);
			break;
		}
	}

	SQ_FUNCTION_CALL(vm, paramSize);
	SQ_FUNCTION_END(vm);
}

void ScriptRPC::ScriptFocus(CNetwork* network, BitStream& stream, Packet* packet)
{
	bool focusType;
	int playerID, focusID;

	stream.Read(focusType);
	stream.Read(playerID);
	stream.Read(focusID);

	focusType ? SCallback::onTakeFocus(playerID, focusID) : SCallback::onLostFocus(playerID, focusID);
}