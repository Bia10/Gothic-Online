#include "..\\stdafx.h"

void ScriptRPC::HandleScriptRPC(CNetwork* network, Packet* packet)
{
	BitStream stream(packet->data,packet->length,false);
	stream.IgnoreBytes(1);

	MessageID eScriptRPC;
	stream.Read(eScriptRPC);
	switch(eScriptRPC)
	{
	case CLIENT_SCRIPT: ScriptLoad(network,stream); break;
	case SCRIPT_PACKET: ScriptPacket(network,stream); break;
	case SCRIPT_UNCONSCIOUS: ScriptUnconscious(network,stream); break;
	case SCRIPT_VISUAL: ScriptVisual(network, stream); break;
	case SCRIPT_CALL: ScriptCall(network, stream); break;
	case SCRIPT_CHECK: ScriptCheck(network, stream); break;
	}
};

void ScriptRPC::ScriptLoad(CNetwork* network, BitStream& stream)
{
	RakString scriptName;
	stream.Read(scriptName);
	scr.StartScript(scriptName.C_String());
};

void ScriptRPC::ScriptPacket(CNetwork* network, BitStream& stream)
{
	RakString data;
	stream.Read(data);
	SCallback::onPacket(data.C_String());
};

void ScriptRPC::ScriptUnconscious(CNetwork* network, BitStream& stream)
{
	bool unconscious;
	stream.Read(unconscious);

	scr.GetScriptVars()->isUnconsciousEnabled = unconscious;
}

void ScriptRPC::ScriptVisual(CNetwork* network, BitStream& stream)
{
	int playerID;
	RakString bodyModel, headModel;
	int bodyTexture, headTexture;

	stream.Read(playerID);

	CPlayer *player = playerManager.GetPlayer(playerID);
	if (playerID != core.GetMultiplayer()->GetMyID() && player)
	{
		stream.Read(bodyModel);
		stream.Read(bodyTexture);
		stream.Read(headModel);
		stream.Read(headTexture);

		player->SetAdditionalVisuals(zSTRING(bodyModel.C_String()), bodyTexture, zSTRING(headModel.C_String()), headTexture);
	}
}

void ScriptRPC::ScriptCall(CNetwork* network, BitStream& stream)
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

void ScriptRPC::ScriptCheck(CNetwork* network, BitStream& stream)
{
	RakString scriptName;
	RakString checksum;
	stream.Read(scriptName);
	stream.Read(checksum);
	md5wrapper wrap;
	char buff[512];
	sprintf(buff, "Multiplayer/Script/%s", scriptName.C_String());
	std::string sum = wrap.getHashFromFile(std::string(buff));

	if( strcmp(checksum.C_String(), sum.c_str()) != 0 )
	{
		network->Disconnect();
		CGameManager::GetGameManager()->ExitGame();
		ExitProcess(0);
	}
}