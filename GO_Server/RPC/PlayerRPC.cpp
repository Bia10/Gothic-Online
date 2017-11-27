#include "../stdafx.h"

void PlayerRPC::HandlePlayerRPC(CNetwork* network, Packet* packet)
{
	BitStream stream(packet->data,packet->length,false);
	stream.IgnoreBytes(1);

	MessageID ePlayerRPC;
	stream.Read(ePlayerRPC);

	switch(ePlayerRPC)
	{
	case SET_POSITION: 
		SetPosition(packet,stream); break;
	case SET_ROTATION:
		SetAngle(packet,stream); break;
	case CHANGE_WEAPONMODE:
		ChangeWeaponMode(packet,stream); break;
	case PLAY_ANIMATION:
		PlayAnimation(packet,stream); break;
	case WEAR_ARMOR:
		WearArmor(packet,stream); break;
	case EQUIP_WEAPON:
		EquipWeapon(packet,stream); break;
	case CHANGE_INSTANCE:
		ChangeInstance(packet,stream); break;
	case ITEM_HAND:
		ItemHand(packet, stream); break;
	case CHANGE_LEVEL:
		ChangeLevel(packet, stream); break;
	case ENTER_WORLD:
		EnterWorld(packet); break;
	case SET_HEALTH:
		SetHealth(packet,stream); break;
	case SET_HEALTH_MAX:
		SetHealthMax(packet,stream); break;
	case ATTACK_HIT:
		AttackHit(packet,stream); break;
	case ATTACK_DEAD:
		AttackDead(packet,stream); break;
	case ATTACK_UNCONSCIOUS:
		AttackUnconscious(packet,stream); break;
	case STAND_UP:
		StandUp(packet,stream); break;
	case MAGIC_SETUP:
		MagicSetup(packet,stream); break;
	case MAGIC_ATTACK:
		MagicAttack(packet,stream); break;
	//case SET_PROTECTION:
		//SetProtection(packet, stream); break;
	//case SET_SKILLWEAPON:
		//SetSkillWeapon(packet, stream); break;
	case SET_OVERLAY:
		SetOverlay(packet, stream); break;
	case SET_TIMED_OVERLAY:
		SetTimedOverlay(packet, stream); break;
	case MOB_TRIGGER:
		MobTrigger(packet, stream); break;
	case SHOOT_ARROW:
		ShootArrow(packet, stream); break;
	}
};

void PlayerRPC::SetPosition(Packet* packet, BitStream& stream)
{
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);
	if( player && player->bConnected == true && player->spawned == true )
	{
		stream.Read(player->x);
		stream.Read(player->y);
		stream.Read(player->z);
		
		BitStream wStream;
		wStream.Write((MessageID)GO_PLAYER);
		wStream.Write((MessageID)SET_POSITION);
		wStream.Write(player->playerId);
		wStream.Write(player->x);
		wStream.Write(player->y);
		wStream.Write(player->z);

		core.GetNetwork()->SendToPlayersOnList(wStream, LOW_PRIORITY, UNRELIABLE, &player->streamedPlayers);
	}
};

void PlayerRPC::SetAngle(Packet* packet, BitStream& stream)
{
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);

	if( player && player->bConnected == true && player->spawned == true )
	{
		stream.Read(player->angle);

		BitStream wStream;
		wStream.Write((MessageID)GO_PLAYER);
		wStream.Write((MessageID)SET_ROTATION);
		wStream.Write(player->playerId);
		wStream.Write(player->angle);

		core.GetNetwork()->SendToPlayersOnList(wStream, LOW_PRIORITY, UNRELIABLE, &player->streamedPlayers);
	}
};

void PlayerRPC::ChangeWeaponMode(Packet* packet, BitStream& stream)
{
	//LOG("PlayerRPC::ChangeWeaponMode");
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);

	if( player && player->bConnected == true && player->spawned == true )
	{
		stream.Read(player->weaponMode);

		BitStream wStream;
		wStream.Write((MessageID)GO_PLAYER);
		wStream.Write((MessageID)CHANGE_WEAPONMODE);
		wStream.Write(player->playerId);
		wStream.Write(player->weaponMode);

		core.GetNetwork()->SendToPlayersOnList(wStream,LOW_PRIORITY,RELIABLE_ORDERED, &player->streamedPlayers);
	}
};

void PlayerRPC::PlayAnimation(Packet* packet, BitStream& stream)
{
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);

	if( player && player->spawned )
	{
		stream.Read(player->animationId);

		BitStream wStream;
		wStream.Write((MessageID)GO_PLAYER);
		wStream.Write((MessageID)PLAY_ANIMATION);
		wStream.Write(player->playerId);
		wStream.Write(player->animationId);

		core.GetNetwork()->SendToPlayersOnList(wStream,LOW_PRIORITY,RELIABLE, &player->streamedPlayers);
	}
};

void PlayerRPC::WearArmor(Packet* packet, BitStream& stream)
{
	//LOG("PlayerRPC::WearArmor");
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);
	if( player && player->bConnected == true && player->spawned == true )
	{
		stream.Read(player->armorInstance);

		BitStream wStream;
		wStream.Write((MessageID)GO_PLAYER);
		wStream.Write((MessageID)WEAR_ARMOR);
		wStream.Write(player->playerId);
		wStream.Write(player->armorInstance);

		core.GetNetwork()->SendToPlayersOnList(wStream,LOW_PRIORITY,RELIABLE, &player->streamedPlayers);
	};
};

void PlayerRPC::EquipWeapon(Packet* packet, BitStream& stream)
{
	//LOG("PlayerRPC::EquipWeapon");
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);
	if( player && player->bConnected == true && player->spawned == true )
	{
		int weaponType;
		stream.Read(weaponType);
		BitStream wStream;
		wStream.Write((MessageID)GO_PLAYER);
		wStream.Write((MessageID)EQUIP_WEAPON);
		wStream.Write(player->playerId);
		wStream.Write(weaponType);
		if(weaponType == 1)
		{
			stream.Read(player->meleeWeaponInstance);
			wStream.Write(player->meleeWeaponInstance);
			//LOG("%s Equip %s", player->name.C_String(), player->meleeWeaponInstance.C_String());
		}
		else if( weaponType == 2 )
		{
			stream.Read(player->rangedWeaponInstance);
			wStream.Write(player->rangedWeaponInstance);
			//LOG("%s Equip %s", player->name.C_String(), player->rangedWeaponInstance.C_String());
		}
		
		core.GetNetwork()->SendToPlayersOnList(wStream,LOW_PRIORITY,RELIABLE_ORDERED, &player->streamedPlayers);
		
	}
};

void PlayerRPC::ChangeInstance(Packet* packet, BitStream& stream)
{
	//LOG("PlayerRPC::ChangeInstance");
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);
	if( player && player->bConnected == true && player->spawned == true )
	{
		stream.Read(player->instance);


		BitStream wStream;
		wStream.Write((MessageID)GO_PLAYER);
		wStream.Write((MessageID)CHANGE_INSTANCE);
		wStream.Write(player->playerId);
		wStream.Write(player->instance);

		core.GetNetwork()->SendToPlayersOnList(wStream,LOW_PRIORITY,RELIABLE_ORDERED, &player->streamedPlayers);

	}
};

void PlayerRPC::ItemHand(Packet* packet, BitStream& stream)
{
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);
	if( player && player->bConnected == true && player->spawned == true )
	{
		int hand;
		RakString handItem;
		stream.Read(hand);
		stream.Read(handItem);

		if( hand == 1 )
		{
			player->leftHand = handItem;
			//LOG("Player %s changed his left hand to %s", player->name.C_String(), player->leftHand.C_String());
		}
		else if( hand == 2 )
		{
			player->rightHand = handItem;
			//LOG("Player %s changed his right hand to %s", player->name.C_String(), player->rightHand.C_String());
		}

		BitStream wStream;
		wStream.Write((MessageID)GO_PLAYER);
		wStream.Write((MessageID)ITEM_HAND);
		wStream.Write(player->playerId);
		wStream.Write(hand);
		wStream.Write(handItem);

		core.GetNetwork()->SendToPlayersOnList(wStream,LOW_PRIORITY,RELIABLE_ORDERED, &player->streamedPlayers);

	}
};

void PlayerRPC::ChangeLevel(Packet* packet, BitStream& stream)
{

	//LOG("PlayerRPC::ChangeLevel");
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);

	if( player && player->bConnected == true && player->spawned == true )
	{
		BitStream s;
		s.Write((MessageID)GO_PLAYER);
		s.Write((MessageID)DESTROY_PLAYER);
		s.Write(player->GetID());
		core.GetNetwork()->SendToPlayersOnList(s,MEDIUM_PRIORITY,RELIABLE, &player->streamedPlayers);

		for (int i = 0; i < player->streamedPlayers.Num(); ++i)
			player->streamedPlayers[i]->streamedPlayers.Remove(player);

		player->streamedPlayers.Clear();

		player->spawned = false;
		stream.Read(player->world);
	}
};

void PlayerRPC::EnterWorld(Packet* packet)
{
	//LOG("PlayerRPC::EnterWorld");
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);
	if( player && player->bConnected == true && player->spawned == false )
	{
		player->spawned = true;

		for (int i = 0; i < core.mobList.Num(); ++i)
		{
			SMobTrigger mob = core.mobList.GetElementByIndex(i);
			if (mob.world == player->world)
			{
				BitStream s;
				s.Write((MessageID)GO_PLAYER);
				s.Write((MessageID)MOB_TRIGGER);
				s.Write(-1);
				s.Write(true);
				s.Write(mob.x);
				s.Write(mob.y);
				s.Write(mob.z);

				core.GetNetwork()->GetPeer()->Send(&s, LOW_PRIORITY, RELIABLE, 0, packet->systemAddress, false);
			}
		}
	}
};

void PlayerRPC::SetHealth(Packet* packet, BitStream& stream)
{
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);

	if( player && player->bConnected == true && player->spawned == true )
	{
		int health;
		stream.Read(health);
		if (health == 0 && !player->isDead)
		{
			SCallback::onDie(player->GetID(), -1);
			player->isDead = true;
		}
		if (player->health == 0 && health > 0)
		{
			SCallback::onRespawn(player->GetID());
			player->isDead = false;
			player->isUnconscious = false;
		}
			
		player->health = health;

		BitStream s;
		s.Write((MessageID)GO_PLAYER);
		s.Write((MessageID)SET_HEALTH);
		s.Write(player->GetID());
		s.Write(player->health);

		core.GetNetwork()->SendToPlayersOnList(s,HIGH_PRIORITY,RELIABLE_ORDERED, &player->streamedPlayers);
	}
};

void PlayerRPC::SetHealthMax(Packet* packet, BitStream& stream)
{
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);

	if( player && player->bConnected == true && player->spawned == true )
	{
		stream.Read(player->maxhealth);

		BitStream s;
		s.Write((MessageID)GO_PLAYER);
		s.Write((MessageID)SET_HEALTH_MAX);
		s.Write(player->GetID());
		s.Write(player->maxhealth);

		core.GetNetwork()->SendToPlayersOnList(s,LOW_PRIORITY,RELIABLE, &player->streamedPlayers);
	}
};

void PlayerRPC::AttackHit(Packet* packet, BitStream& stream)
{
	int focusID;
	int minushp;
	stream.Read(focusID);
	stream.Read(minushp);
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);
	CPlayer* focusPlayer = playerManager.GetPlayer(focusID);
	if( player && player->bConnected == true && player->spawned == true )
	{
		if (focusPlayer && focusPlayer->bConnected == true && focusPlayer->spawned == true)
		{
			int range = -1;
			// Calculate range
			{
				int rangeRight, rangeLeft;
				if (player->angle >= focusPlayer->angle)
				{
					rangeRight = player->angle - focusPlayer->angle;
					rangeLeft = (focusPlayer->angle + 360) - player->angle;
				}
				else
				{
					rangeRight = focusPlayer->angle - player->angle;
					rangeLeft = (player->angle + 360) - focusPlayer->angle;
				}

				rangeRight <= rangeLeft ? range = rangeRight : range = rangeLeft;
			}
			
			// Block on server side
			if (focusPlayer->animationId != 392 && focusPlayer->animationId != 447 && focusPlayer->animationId != 791 ||
			   (focusPlayer->animationId == 392 || focusPlayer->animationId == 447 || focusPlayer->animationId == 791) &&
				range <= 100)
			{
				SCallback::onHit(player->GetID(), focusID);

				BitStream s;
				s.Write((MessageID)GO_PLAYER);
				s.Write((MessageID)ATTACK_HIT);
				s.Write(player->playerId);
				s.Write(minushp);

				core.GetNetwork()->GetPeer()->Send(&s, HIGH_PRIORITY, RELIABLE_ORDERED, 0, focusPlayer->GetAddress(), false);
			}
			else
			{
				BitStream s;
				s.Write((MessageID)GO_PLAYER);
				s.Write((MessageID)SET_HEALTH);
				s.Write(focusPlayer->playerId);
				s.Write(focusPlayer->health);
				core.GetNetwork()->GetPeer()->Send(&s, HIGH_PRIORITY, RELIABLE_ORDERED, 0, player->GetAddress(), false);
			}
		}
	}
};

void PlayerRPC::AttackDead(Packet* packet, BitStream& stream)
{
	int focusID;
	stream.Read(focusID);
	CPlayer* focusPlayer = playerManager.GetPlayer(focusID);
	CPlayer* killerPlayer = playerManager.GetPlayer(packet->systemAddress);
	if (focusPlayer && focusPlayer->bConnected && focusPlayer->spawned && !focusPlayer->isDead &&
		killerPlayer && killerPlayer->bConnected && killerPlayer->spawned && !killerPlayer->isDead)
	{
		focusPlayer->isDead = true;
		SCallback::onDie(focusPlayer->GetID(), killerPlayer->GetID());

		BitStream s;
		s.Write((MessageID)GO_PLAYER);
		s.Write((MessageID)ATTACK_DEAD);

		core.GetNetwork()->GetPeer()->Send(&s, LOW_PRIORITY, RELIABLE, 0, focusPlayer->GetAddress(), false);
	}
	else if (killerPlayer->isDead)
	{
		BitStream s;
		s.Write((MessageID)GO_PLAYER);
		s.Write((MessageID)FORCE_STANDUP);
		s.Write(focusID);
		s.Write(focusPlayer->health);

		core.GetNetwork()->GetPeer()->Send(&s, LOW_PRIORITY, RELIABLE, 0, packet->systemAddress, false);
	}
};

void PlayerRPC::AttackUnconscious(Packet* packet, BitStream& stream)
{
	int focusID;
	stream.Read(focusID);

	CPlayer* focusPlayer = playerManager.GetPlayer(focusID);
	CPlayer* killerPlayer = playerManager.GetPlayer(packet->systemAddress);

	if (focusPlayer && focusPlayer->bConnected && focusPlayer->spawned && !focusPlayer->isUnconscious &&
		killerPlayer && killerPlayer->bConnected && killerPlayer->spawned && !killerPlayer->isUnconscious)
	{
		focusPlayer->isUnconscious = true;
		SCallback::onUnconscious(focusPlayer->GetID(), playerManager.GetPlayer(packet->systemAddress)->GetID());

		BitStream s;
		s.Write((MessageID)GO_PLAYER);
		s.Write((MessageID)ATTACK_UNCONSCIOUS);
		s.Write(focusID);
		s.Write(killerPlayer->GetID());

		core.GetNetwork()->SendToPlayersOnList(s, LOW_PRIORITY, RELIABLE, &killerPlayer->streamedPlayers);
	}
	else if (killerPlayer->isUnconscious)
	{
		BitStream s;
		s.Write((MessageID)GO_PLAYER);
		s.Write((MessageID)FORCE_STANDUP);
		s.Write(focusID);
		s.Write(focusPlayer->health);

		core.GetNetwork()->GetPeer()->Send(&s, LOW_PRIORITY, RELIABLE, 0, packet->systemAddress, false);
	}
};

void PlayerRPC::StandUp(Packet* packet, BitStream& stream)
{
	//LOG("PlayerRPC::StandUp");
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);

	if (player && player->bConnected == true && player->spawned == true && !player->isDead)
	{
		player->isUnconscious = false;
		SCallback::onStandUp(player->GetID());

		bool unconscious;
		stream.Read(unconscious);

		BitStream s;
		s.Write((MessageID)GO_PLAYER);
		s.Write((MessageID)STAND_UP);
		s.Write(player->GetID());
		s.Write(unconscious);

		core.GetNetwork()->SendToPlayersOnList(s,LOW_PRIORITY,RELIABLE, &player->streamedPlayers);
	}
};

void PlayerRPC::MagicSetup(Packet* packet, BitStream& stream)
{
	//LOG("PlayerRPC::MagicSetup");
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);
	if( player && player->bConnected == true && player->spawned == true )
	{
		stream.Read(player->magicItem);

		BitStream s;
		s.Write((MessageID)GO_PLAYER);
		s.Write((MessageID)MAGIC_SETUP);
		s.Write(player->GetID());
		s.Write(player->magicItem);

		core.GetNetwork()->SendToPlayersOnList(s,LOW_PRIORITY,RELIABLE, &player->streamedPlayers);
	}
};

void PlayerRPC::MagicAttack(Packet* packet, BitStream& stream)
{
	//LOG("PlayerRPC::MagicAttack");
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);
	if( player && player->bConnected == true && player->spawned == true )
	{
		int focusID;
		stream.Read(focusID);

		BitStream s;
		s.Write((MessageID)GO_PLAYER);
		s.Write((MessageID)MAGIC_ATTACK);
		s.Write(player->GetID());
		s.Write(focusID);
		
		core.GetNetwork()->SendToPlayersOnList(s,LOW_PRIORITY, UNRELIABLE, &player->streamedPlayers);
	}
};
/*
void PlayerRPC::SetProtection(Packet* packet, BitStream& stream)
{
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);
	if (player && player->bConnected == true && player->spawned == true)
	{
		int index;
		stream.Read(index);
		stream.Read(player->protection[index]);

		BitStream s;
		s.Write((MessageID)GO_PLAYER);
		s.Write((MessageID)SET_PROTECTION);
		s.Write(player->GetID());
		s.Write(index);
		s.Write(player->protection[index]);

		core.GetNetwork()->SendToPlayersOnList(s, MEDIUM_PRIORITY, RELIABLE_ORDERED, &player->streamedPlayers);
	}
};
*/

void PlayerRPC::SetOverlay(Packet* packet, BitStream& stream)
{
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);
	if (player && player->bConnected == true && player->spawned == true)
	{
		bool add;
		RakString overlay;
		stream.Read(add);
		stream.Read(overlay);

		if (add)
			player->overlaysList.PushBack(overlay);
		else
		{
			if (!player->overlaysList.Remove(overlay))
				return;
		}
			
		BitStream s;
		s.Write((MessageID)GO_PLAYER);
		s.Write((MessageID)SET_OVERLAY);
		s.Write(player->GetID());
		s.Write(add);
		s.Write(overlay);
	
		core.GetNetwork()->SendToPlayersOnList(s, MEDIUM_PRIORITY, RELIABLE, &player->streamedPlayers);
	}
}

void PlayerRPC::SetTimedOverlay(Packet* packet, BitStream& stream)
{
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);
	if (player && player->bConnected == true && player->spawned == true)
	{
		TimeMS time;
		RakString overlay;
		stream.Read(time);
		stream.Read(overlay);

		player->timedOverlays.PushBack(STimedOverlay(GetTimeMS() + time - 300, overlay));

		BitStream s;
		s.Write((MessageID)GO_PLAYER);
		s.Write((MessageID)SET_OVERLAY);
		s.Write(player->GetID());
		s.Write(true);
		s.Write(overlay);

		core.GetNetwork()->SendToPlayersOnList(s, MEDIUM_PRIORITY, RELIABLE, &player->streamedPlayers);
	}
}

void PlayerRPC::MobTrigger(Packet* packet, BitStream& stream)
{
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);
	if (player && player->bConnected == true && player->spawned == true)
	{
		bool trigger;
		float x, y, z;
		RakString world;
		stream.Read(trigger);
		stream.Read(world);
		stream.Read(x);
		stream.Read(y);
		stream.Read(z);

		SMobTrigger mobTrigger(x, y, z, world);
		int index = core.mobList.FindIndex(mobTrigger);
		if (trigger && index == -1 ||
			!trigger && index != -1)
		{

			if (index == -1)
				core.mobList.PushBack(mobTrigger);
			else
				core.mobList.RemoveIndex(index);

			BitStream s;
			s.Write((MessageID)GO_PLAYER);
			s.Write((MessageID)MOB_TRIGGER);
			s.Write(player->GetID());
			s.Write(trigger);
			s.Write(x);
			s.Write(y);
			s.Write(z);

			core.GetNetwork()->SendToAllInWorld(s, LOW_PRIORITY, RELIABLE_ORDERED, world, player);
		}
	}
}

void PlayerRPC::ShootArrow(Packet* packet, BitStream& stream)
{
	CPlayer* player = playerManager.GetPlayer(packet->systemAddress);
	if (player && player->bConnected == true && player->spawned == true)
	{
		int targetID, aniID, type;

		stream.Read(targetID);
		stream.Read(aniID);
		stream.Read(type);

		BitStream s;
		s.Write((MessageID)GO_PLAYER);
		s.Write((MessageID)SHOOT_ARROW);
		s.Write(player->GetID());
		s.Write(targetID);
		s.Write(aniID);
		s.Write(type);

		core.GetNetwork()->SendToPlayersOnList(s, HIGH_PRIORITY, RELIABLE, &player->streamedPlayers);
	}
}