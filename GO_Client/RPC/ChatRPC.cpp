#include "..\\stdafx.h"

void ChatRPC::HandleChatRPC(CNetwork* network, Packet* packet)
{
	DLOG("ChatRPC::HandleChatRPC()");
	BitStream stream(packet->data,packet->length,false);
	stream.IgnoreBytes(1);
	
	MessageID eChatRPC;
	stream.Read(eChatRPC);

	switch(eChatRPC)
	{
	case CHAT_MESSAGE: ServerMessage(network,stream); break;
	case MESSAGE_RGB: MessageRGB(network,stream); break;
	}
};

void ChatRPC::ServerMessage(CNetwork* network, BitStream& stream)
{
	DLOG("ChatRPC::ServerMessage()");
	RakString message;
	stream.Read(message);

	core.GetChat()->AddLine(message, zCOLOR(255,255,255,255)); //Bia³y xd
};

void ChatRPC::MessageRGB(CNetwork* network, BitStream& stream)
{
	DLOG("ChatRPC::MessageRGB()");
	RakString message;
	int r,g,b;
	stream.Read(message);
	stream.Read(r);
	stream.Read(g);
	stream.Read(b);

	core.GetChat()->AddLine(message, zCOLOR(r,g,b,255));
};