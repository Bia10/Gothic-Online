#include "stdafx.h"

CStreamer::CStreamer()
{
	timeStreamPlayers = 0;
	timeStreamItems = 0;
};

CStreamer::~CStreamer(){};

void CStreamer::Pulse()
{
	StreamPlayers(true);
	StreamItems();
};

void CStreamer::StreamPlayers(bool timeout)
{
	if (!timeout || timeout && timeStreamPlayers < GetTimeMS())
	{
		unsigned numOfPlayers = playerManager.GetNumberOfPlayers();
		if (numOfPlayers > 1)
		{
			for (playerListIter i = playerManager.playerList.begin(); i != playerManager.playerList.end(); ++i)
			{
				CPlayer *player = i->second;

				if (player->spawned)
				{
					for (playerListIter j = playerManager.playerList.begin(); j != playerManager.playerList.end(); ++j)
					{
						if (i->first != j->first)
						{
							CPlayer *streamed = j->second;

							if (streamed->spawned && !streamed->isInvisible &&
								streamed->GetVirutalWorld() == player->virtualWorld &&
								streamed->world == player->world)
							{
								float distance = goMath::GetDistance3D(streamed->x, streamed->y, streamed->z, player->x, player->y, player->z);

								if (distance <= STREAM_DISTANCE && !IsPlayerStreamedToPlayer(streamed, player))
								{
									playerManager.CreatePlayerForOtherPlayer(streamed, player);
									player->streamedPlayers.PushBack(streamed);
								}
								else if (distance > STREAM_DISTANCE && IsPlayerStreamedToPlayer(streamed, player))
								{
									BitStream stream;
									stream.Write((MessageID)GO_PLAYER);
									stream.Write((MessageID)DESTROY_PLAYER);
									stream.Write(streamed->GetID());
									core.GetNetwork()->GetPeer()->Send(&stream, LOW_PRIORITY, RELIABLE, 0, player->GetAddress(), false);
									player->streamedPlayers.Remove(streamed);
								}
							}
						}
					}
				}
			}
		}

		timeStreamPlayers = GetTimeMS() + STREAM_TIME;
	}
};

void CStreamer::StreamItems()
{
	if( timeStreamItems < GetTimeMS() )
	{
		unsigned int numOfPlayers = playerManager.GetNumberOfPlayers();
		unsigned int numOfItems = itemManager.GetNumberOfItems();
		if( numOfPlayers > 0 )
		{
			CPlayer* player = NULL;
			CItem* item = NULL;

			for( playerListIter i = playerManager.playerList.begin(); i != playerManager.playerList.end(); ++i )
			{
				if( i != playerManager.playerList.end() )
				{
				player = i->second;
				for( unsigned int j = 0; j < numOfItems; ++j )
				{
					item = itemManager.itemList[j];
					float x, y, z;
					item->GetPositionXYZ(x,y,z);
					if( goMath::GetDistance3D(player->x, player->y, player->z, x, y, z) <= STREAM_DISTANCE && player->world.StrCmp(item->GetWorldName()) == 0 )
					{
						if( IsItemStreamedToPlayer(item,player) == false )
							itemManager.CreateItemForPlayer(item, player);
					}
					else if( IsItemStreamedToPlayer(item,player) == true )
						itemManager.DestroyItemForPlayer(item,player);
				}
				}
			}
		}
		timeStreamItems = GetTimeMS() + ITEM_STREAM_TIME;
	}
};

bool CStreamer::IsPlayerStreamedToPlayer(CPlayer* p1, CPlayer* p2)	//Returns true if p1 is streamed to p2
{
	if( p1 && p2 )
	{
		if( p2->streamedPlayers.FindIndex(p1) != -1 )
			return true;
	}
	return false;
};

bool CStreamer::IsItemStreamedToPlayer(CItem* item, CPlayer* player)
{
	if( player->streamedItems.FindIndex(item) == -1 )
		return false;
	else return true;
};