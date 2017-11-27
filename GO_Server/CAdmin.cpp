#include "stdafx.h"

CAdmin::CAdmin()
{
};

CAdmin::~CAdmin()
{
};

void CAdmin::HandleAdminCommand(CPlayer* player, RakString command)
{
	if( player )
	{
		CNetwork* n = core.GetNetwork();
		size_t pos = -1;
		if( (pos = command.Find(" ")) != (size_t)-1 )
		{
			LOG("[admin] param found!");
			RakString cmd = command;
			cmd.Erase(pos, cmd.GetLength()-pos);
			RakString params = command;
			params.Erase(0, pos+1);

			if( player->isAdmin == false )
			{
				if(	cmd.StrCmp("login") == 0 )
				{
					if( params.StrCmp(core.GetConfig()->GetAdminPassword()) == 0 )
					{
						player->isAdmin = true;
						BitStream s;
						s.Write((MessageID)GO_CHAT);
						s.Write((MessageID)CHAT_MESSAGE);
						s.Write(RakString("(SERVER): Admin access granted!"));
						n->GetPeer()->Send(&s, LOW_PRIORITY, RELIABLE, 0 , player->GetAddress(), false);
					}
					else
					{
						BitStream s;
						s.Write((MessageID)GO_CHAT);
						s.Write((MessageID)CHAT_MESSAGE);
						s.Write(RakString("(SERVER): Bad admin password."));
						n->GetPeer()->Send(&s, LOW_PRIORITY, RELIABLE, 0 , player->GetAddress(), false);
					}
				}
			}
			else
			{
				if( cmd.StrCmp("say") == 0 )
				{
					BitStream s;
					s.Write((MessageID)GO_CHAT);
					s.Write((MessageID)CHAT_MESSAGE);
					s.Write(RakString("(SERVER): ")+params);

					n->SendToAll(s,LOW_PRIORITY,RELIABLE);
				}
				else if( cmd.StrCmp("ban") == 0 )
				{
					CPlayer* banplayer = playerManager.GetPlayer(params);
					if( banplayer )
					{
						if( core.GetBanSystem()->BanPlayer(banplayer, BAN_LIST) == true )
						{
							BitStream s;
							s.Write((MessageID)GO_CHAT);
							s.Write((MessageID)CHAT_MESSAGE);
							s.Write(RakString("(SERVER): Player %s has been silent-banned", params.C_String()));

							n->GetPeer()->Send(&s, LOW_PRIORITY, RELIABLE, 0 , player->GetAddress(), false);
						}
						else
						{
							BitStream s;
							s.Write((MessageID)GO_CHAT);
							s.Write((MessageID)CHAT_MESSAGE);
							s.Write(RakString("(SERVER): Error, cannot ban player. Maybe he isn't exists?"));

							n->GetPeer()->Send(&s, LOW_PRIORITY, RELIABLE, 0 , player->GetAddress(), false);
						}
					}
				}
				else
				{
					SCallback::onAdminCommand(player->GetID(), cmd.C_String());
				}
			}
			command.FreeMemory();
			cmd.FreeMemory();
			params.FreeMemory();
		}
	}
};