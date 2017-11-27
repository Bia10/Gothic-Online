#include "../stdafx.h"

void ChatRPC::HandleChatRPC(CNetwork* network, Packet* packet)
{
	BitStream stream(packet->data,packet->length,false);
	stream.IgnoreBytes(1);

	MessageID eChatRPC;
	stream.Read(eChatRPC);
	if(eChatRPC == CHAT_MESSAGE)
	{
	 PlayerMessage(network,stream);
	}
};

void ChatRPC::PlayerMessage(CNetwork* network, BitStream& stream)
{
#ifdef DEBUG_MODE
	LOG("ChatRPC::PlayerMessage");
#endif
	int playerID;
	RakString playerMessage;

	stream.Read(playerID);
	stream.Read(playerMessage);
#ifdef DEBUG_MODE
	LOG("ChatRPC::PlayerMessage(%s)", playerMessage.C_String());
#endif

	if(playerMessage.GetLength() <= 255)
	{
		CPlayer* player = playerManager.GetPlayer(playerID);
		if( player )
		{
			if( playerMessage.GetLength() >= 2 )
			{
				if( playerMessage.Find(".")  == 0 )
				{
					playerMessage.Erase(0, 1);
					CAdmin adm;
					adm.HandleAdminCommand(player,playerMessage);
				}
				else if( playerMessage.Find("/") == 0 )
				{
					std::string text = playerMessage.C_String();
					int pos = text.find(' ');
				
					SCallback::onCommand(player->GetID(),text.substr(1, pos - 1).c_str(), pos == std::string::npos ? "" : text.substr(pos + 1).c_str());
				}
				else
				{
					if (SCallback::onMessage(player->GetID(), playerMessage.C_String()) == 0)
					{
						BitStream chatStream;
						chatStream.Write((MessageID)GO_CHAT);
						chatStream.Write((MessageID)CHAT_MESSAGE);
						chatStream.Write(RakString("%s: %s", player->name.C_String(), playerMessage.C_String()));
	
						network->SendToAll(chatStream,HIGH_PRIORITY,RELIABLE);
						LOG("[chat] %s: %s", player->name.C_String(), playerMessage.C_String());
					}
				}
			}
			else
			{
				if( SCallback::onMessage(player->GetID(), playerMessage.C_String()) == 0 )
				{
					BitStream chatStream;
					chatStream.Write((MessageID)GO_CHAT);
					chatStream.Write((MessageID)CHAT_MESSAGE);
					chatStream.Write(RakString("%s: %s", player->name.C_String(), playerMessage.C_String()));
	
					network->SendToAll(chatStream,HIGH_PRIORITY,RELIABLE);
					LOG("[chat] %s: %s", player->name.C_String(), playerMessage.C_String());
				}
			}
		}
	}
	playerMessage.FreeMemory();
};