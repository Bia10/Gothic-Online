#include "..\\stdafx.h"

void PlayerRPC::HandlePlayerRPC(CNetwork* network, Packet* packet)
{
	//DLOG("PlayerRPC::HandlePlayerRPC()");

	BitStream stream(packet->data, packet->length, false);
	stream.IgnoreBytes(1);

	MessageID ePlayerRPC;
	stream.Read(ePlayerRPC);

	switch(ePlayerRPC)
	{
	case CREATE_PLAYER: //Local player is here
		CreatePlayer(network, stream); break;
	case CREATE_AND_SPAWN:
		CreateAndSpawnPlayer(stream); break;
	case DESTROY_PLAYER:
		DestroyPlayer(network,stream); break;
	case SET_POSITION:
		SetPosition(stream); break;
	case SET_ROTATION:
		SetAngle(stream); break;
	case CHANGE_WEAPONMODE:
		ChangeWeaponMode(stream); break;
	case PLAY_ANIMATION:
		PlayAnimation(stream); break;
	case WEAR_ARMOR:
		WearArmor(stream); break;
	case EQUIP_WEAPON:
		EquipWeapon(stream); break;
	case CHANGE_INSTANCE:
		ChangeInstance(stream); break;
	case ITEM_HAND:
		ItemHand(stream); break;
	case SET_HEALTH:
		SetHealth(stream); break;
	case SET_HEALTH_MAX:
		SetHealthMax(stream); break;
	case ATTACK_HIT:
		AttackHit(stream); break;
	case ATTACK_DEAD:
		AttackDead(stream); break;
	case ATTACK_UNCONSCIOUS:
		AttackUnconscious(stream); break;
	case STAND_UP:
		StandUp(stream); break;
	case MAGIC_SETUP:
		MagicSetup(stream); break;
	case MAGIC_ATTACK:
		MagicAttack(stream); break;
	case PLAYER_LIST:
		PlayerList(stream); break;
	//case SET_PROTECTION:
		//SetProtection(stream); break;
	case SET_OVERLAY:
		SetOverlay(stream); break;
	case MOB_TRIGGER:
		MobTrigger(stream); break;
	case SHOOT_ARROW:
		ShootArrow(stream); break;
	case FORCE_STANDUP:
		ForceStandUp(stream);  break;
	}
};

void PlayerRPC::CreatePlayer(CNetwork* network, BitStream& stream)
{
	DLOG("PlayerRPC::CreatePlayer()");
	int playerID;
	RakString playerName;

	stream.Read(playerID);
	stream.Read(playerName);

	if (core.GetMultiplayer()->GetMyID() == playerID)
		playerManager.CreateLocalPlayer(playerID, playerName);
};

void PlayerRPC::CreateAndSpawnPlayer(BitStream& stream)
{
	DLOG("PlayerRPC::CreateAndSpawnPlayer()");
	int playerID;
	RakString playerName;
	RakString instanceName;

	stream.Read(playerID);
	stream.Read(playerName);
	if( playerID != core.GetMultiplayer()->GetMyID() && !playerManager.GetPlayer(playerID) )
	{
		RakString bodyModel, headModel, overlay;
		int bodyTexture, headTexture;
		//int protection[4]

		stream.Read(instanceName);

	CPlayer* player = playerManager.CreatePlayer(playerID, playerName);
		if( player )
		{
			stream.Read(bodyModel);
			stream.Read(bodyTexture);
			stream.Read(headModel);
			stream.Read(headTexture);
			/*stream.Read(protection[0]);
			stream.Read(protection[1]);
			stream.Read(protection[2]);
			stream.Read(protection[3]);*/
			stream.Read(player->pos.x);
			stream.Read(player->pos.y);
			stream.Read(player->pos.z);
			stream.Read(player->angle);
			stream.Read(player->maxhealth);
			stream.Read(player->health);
			stream.Read(player->armorInstance);
			stream.Read(player->rangedWeaponInstance);
			stream.Read(player->meleeWeaponInstance);
			stream.Read(player->weaponMode);
			stream.Read(player->leftHand);
			stream.Read(player->rightHand);

			player->Spawn(player->pos.x, player->pos.y, player->pos.z, instanceName);
			if( player->npc != NULL )
			{
				player->SetAdditionalVisuals(zSTRING(bodyModel.C_String()), bodyTexture, zSTRING(headModel.C_String()), headTexture);
				/*player->npc->SetProtection(PROT_WEAPON, protection[0]);
				player->npc->SetProtection(PROT_ARROW, protection[1]);
				player->npc->SetProtection(PROT_FIRE, protection[2]);
				player->npc->SetProtection(PROT_MAGIC, protection[3]);*/
				player->npc->SetHeading(player->angle);
				player->npc->SetAttribute(NPC_ATR_HITPOINTS_MAX, player->maxhealth);
				player->npc->SetAttribute(NPC_ATR_HITPOINTS, player->health);
				player->npc->SetWeaponMode2((oCNpc_WeaponMode)player->weaponMode);

				oCItem *leftHand = player->npc->CreateItem(zSTRING(player->leftHand.C_String()), 1);
				if (leftHand)
					player->npc->SetLeftHand(leftHand);

				oCItem *rightHand = player->npc->CreateItem(zSTRING(player->rightHand.C_String()), 1);
				if (rightHand)
					player->npc->SetRightHand(rightHand);

				oCItem *armor = player->npc->CreateItem(zSTRING(player->armorInstance.C_String()), 1);
				if (armor)
					player->npc->Equip(armor);

				oCItem *rangedWeapon = player->npc->CreateItem(zSTRING(player->rangedWeaponInstance.C_String()), 1);
				if (armor)
					player->npc->Equip(rangedWeapon);

				oCItem *meeleWeapon = player->npc->CreateItem(zSTRING(player->meleeWeaponInstance.C_String()), 1);
				if (armor)
					player->npc->Equip(meeleWeapon);
			}
		}
	}
	else 
		playerManager.CreateLocalPlayer(playerID,playerName);

};

void PlayerRPC::DestroyPlayer(CNetwork* network, BitStream& stream)
{
	DLOG("PlayerRPC::DestroyPlayer()");

	int playerID;
	
	stream.Read(playerID);
	if( playerID != core.GetMultiplayer()->GetMyID() )
	{
		CPlayer* player = playerManager.GetPlayer(playerID);
		if( player )
			playerManager.DestroyPlayer(player);
	}
};

void PlayerRPC::SetPosition(BitStream& stream)
{
	DLOG("PlayerRPC::SetPosition()");
	int playerID;
	stream.Read(playerID);

	if( playerID != core.GetMultiplayer()->GetMyID())
	{
		CPlayer* player = playerManager.GetPlayer(playerID);
		if( player )
		{
			//LOG("got pos packet from %s", player->name.C_String());
			stream.Read(player->pos.x);
			stream.Read(player->pos.y);
			stream.Read(player->pos.z);

			/*if( player->npc != NULL )	
				player->npc->SetPosition(player->pos.x, player->pos.y, player->pos.z);*/
		}
	}
};

void PlayerRPC::SetAngle(BitStream& stream)
{
	DLOG("PlayerRPC::SetAngle()");
	int playerID;
	stream.Read(playerID);

	if(core.GetMultiplayer()->GetMyID() != playerID)
	{
		CPlayer* player = playerManager.GetPlayer(playerID);
		if( player )
		{
			stream.Read(player->angle);
			if (player->npc != NULL && player->angle >= 0.0f)
			{
				if (player->npc->GetAttribute(NPC_ATR_HITPOINTS) > 0 && player->npc->IsUnconscious() == 0)
					player->npc->SetHeading(player->angle);
			}
		}
	}
};

void PlayerRPC::ChangeWeaponMode(BitStream& stream)
{
	DLOG("Change weaponmode");
	int playerID;

	stream.Read(playerID);

	if(core.GetMultiplayer()->GetMyID() != playerID)
	{
		CPlayer* player = playerManager.GetPlayer(playerID);
		if( player )
		{
			stream.Read(player->weaponMode);
			if( player->npc != NULL )
			{
				if( player->npc->GetAttribute(NPC_ATR_HITPOINTS) > 0 && player->npc->IsUnconscious() == 0 )
				{
					if( player->npc->GetWeaponMode() != player->weaponMode )
					{
						oCItem *item = NULL;
						switch (player->weaponMode)
						{
						case NPC_WEAPON_1HS:
						case NPC_WEAPON_2HS:
							item = player->npc->GetEquippedMeleeWeapon();
							if (item)
								player->npc->UnequipItem(item);

							player->meleeWeaponInstance = "NULL";
							break;

						case NPC_WEAPON_BOW:
						case NPC_WEAPON_CBOW:
							item = player->npc->GetEquippedRangedWeapon();
							if (item)
								player->npc->UnequipItem(item);

							player->rangedWeaponInstance = "NULL";
							break;
						}
						
						// Repair hand item
						if (strcmp(player->leftHand.C_String(), "NULL") != 0 && !player->npc->GetLeftHand())
						{
							oCItem *item = player->npc->CreateItem(zSTRING(player->leftHand.C_String()), 1);
							if (item)
								player->npc->SetLeftHand(item);
						}

						if (strcmp(player->rightHand.C_String(), "NULL") != 0 && !player->npc->GetRightHand())
						{
							oCItem *item = player->npc->CreateItem(zSTRING(player->rightHand.C_String()), 1);
							if (item)
								player->npc->SetRightHand(item);
						}
					}
				}
			}
		}
	}
};

void PlayerRPC::PlayAnimation(BitStream& stream)
{
	DLOG("PlayerRPC::PlayAnimation()");
	int playerID;

	stream.Read(playerID);
	if( core.GetMultiplayer()->GetMyID() != playerID )
	{
		CPlayer* player = playerManager.GetPlayer(playerID);
		if( player && player->npc)
		{
			int oldAni = player->animationId;
			stream.Read(player->animationId);
			//DLOG("Ani %d SM %d", player->animationId, startMode);

			if (player->npc->GetAttribute(NPC_ATR_HITPOINTS) > 0 && !player->npc->IsUnconscious())
			{
				if (player->animationId != 341 ) //Animacja wywolywana przy zmianie postaci z potwora na ludzka
				{
					zCModel* model = player->npc->GetModel();
					if (model)
						model->StartAni(player->animationId, 0); //uruchomienie nowej animacji
				}
				else
				{
					//DLOG("ANI: 341!!");
					if( player->npc->IsHuman() ) //W innych przypadkach jest crash
					{
						zCModel* model = player->npc->GetModel();
						if( model )
							model->StartAni(player->animationId, 0); //uruchomienie nowej animacji
					}
					/*zCModel* model = player->npc->GetModel();
					if( model )
						model->FadeOutAnisLayerRange(1,2000);*/
				}
			}
		}
	}
};

void PlayerRPC::WearArmor(BitStream& stream)
{
	DLOG("PlayerRPC::WearArmor()");
	int playerID;
	stream.Read(playerID);
	if( core.GetMultiplayer()->GetMyID() != playerID )
	{
		CPlayer* player = playerManager.GetPlayer(playerID);
		if( player && player->npc )
		{
			stream.Read(player->armorInstance);
			if( player->npc->GetAttribute(NPC_ATR_HITPOINTS) > 0 && player->npc->IsUnconscious() == 0 && player->npc->IsHuman() == 1 )
			{
				oCItem* armor = player->npc->GetEquippedArmor();
				if( armor )
				{
					if(strcmp(player->armorInstance.C_String(), armor->GetInstanceName().ToChar()) != 0)
					{
						if(strcmp(player->armorInstance.C_String(), "NULL") == 0)
						{
							DLOG("Remove armor");
							player->npc->UnequipItem(armor);
							player->npc->DoDropVob(armor);
							armor->RemoveVobFromWorld();
						}
						else
						{
							DLOG("Equip armor");
							player->npc->UnequipItem(armor);
							player->npc->DoDropVob(armor);
							armor->RemoveVobFromWorld();
							armor = player->npc->CreateItem(zSTRING(player->armorInstance.C_String()), 1);
							if(armor)
								player->npc->Equip(armor);
						}
					}
				}
				else if( !armor )
				{
					if(strcmp(player->armorInstance.C_String(), "NULL") != 0)
					{
						DLOG("Equip armor");
						armor = player->npc->CreateItem(zSTRING(player->armorInstance.C_String()), 1);
						if(armor)
							player->npc->Equip(armor);
					}
				}
			}
		}
	}
};
void PlayerRPC::EquipWeapon(BitStream& stream)
{
	DLOG("PlayerRPC::EquipWeapon()");
	int playerID;
	int weaponType;
	RakString instance;
	stream.Read(playerID);
	stream.Read(weaponType);
	stream.Read(instance);
	CPlayer* player = playerManager.GetPlayer(playerID);
	if (player && playerID != core.GetMultiplayer()->GetMyID())
	{
		if( !instance.IsEmpty() )
		{
			DLOG("instance isnt empty");
			const char* weaponInstance = instance.C_String();
			if( player->npc )
			{
				DLOG("npc is exist");
				if( player->npc->IsHuman() )
				{
					DLOG("npc is already human");
					player->npc->SetAttribute(NPC_ATR_DEXTERITY, 1000);
					player->npc->SetAttribute(NPC_ATR_STRENGTH, 1000);
					if( weaponType == 1 )
					{
						DLOG("melee");
						player->meleeWeaponInstance = weaponInstance;
						//Melee
						if( strcmp("NULL", weaponInstance) == 0 )
						{
							DLOG("isnull");
							oCItem* melee = player->npc->GetEquippedMeleeWeapon();
							if( melee )
							{
								DLOG("w exists");
								player->npc->UnequipItem(melee);
							}
						}
						else
						{
							DLOG("isntnull");
							oCItem* new_melee = player->npc->CreateItem(zSTRING(weaponInstance),1);
							if (new_melee)
							{
								player->npc->Equip(new_melee);
							}
						}
					
					}
					else if( weaponType == 2 )
					{
						DLOG("ranged");
						player->rangedWeaponInstance = weaponInstance;
						//Ranged
						if( strcmp("NULL", weaponInstance) == 0 )
						{
							DLOG("isnull");
							oCItem* ranged = player->npc->GetEquippedRangedWeapon();
							if( ranged )
							{
								DLOG("w exist");
								player->npc->UnequipItem(ranged);
							}
						}
						else
						{
							DLOG("isntnull");
							oCItem* new_ranged = player->npc->CreateItem(zSTRING(weaponInstance),1);
							if (new_ranged)
							{
								player->npc->Equip(new_ranged);
							}
						}
					}
				}
			}
		}
	}
};

void PlayerRPC::ChangeInstance(BitStream& stream)
{
	DLOG("PlayerRPC::ChangeInstance()");
	int playerID;
	stream.Read(playerID);

	if( core.GetMultiplayer()->GetMyID() != playerID )
	{
		CPlayer* player = playerManager.GetPlayer(playerID);
		if( player )
		{
			stream.Read(player->instance);

			oCNpc* new_npc = oCGame::GetGame()->CreateNPC(zSTRING(player->instance.C_String()), player->pos.x, player->pos.y, player->pos.z);
			if( new_npc )
			{
				oCNpc* old_npc = player->npc;
				old_npc->GetModel()->FadeOutAnisLayerRange(1,2000);
				player->npc = new_npc;
				new_npc->SetHeading(player->angle);
				//Sprawdzenie czy nie jest botem
				if( new_npc->IsMonster() || new_npc->IsGoblin() || new_npc->IsHalfMonster() )
					new_npc->SetAI(NULL); //Po takim zabiegu niestety animki scinaja
				new_npc->SetName(zSTRING(RakString("%s (%d)", player->name.C_String(), player->GetID()).C_String()));
				if( old_npc )
					old_npc->DestroyNpc();
			}
		}
	}
};

void PlayerRPC::ItemHand(BitStream& stream)
{
	DLOG("PlayerRPC::ItemHand()");
	int playerID;
	int hand;
	RakString handInstance;
	stream.Read(playerID);
	stream.Read(hand);
	stream.Read(handInstance);

	if( core.GetMultiplayer()->GetMyID() != playerID )
	{
		CPlayer* player = playerManager.GetPlayer(playerID);
		if( player )
		{
			if( hand == 1 )
				player->leftHand = handInstance;
			else if( hand == 2 )
				player->rightHand = handInstance;

			if( player->npc )
			{
				if( player->npc->IsHuman() )
				{
					if( hand == 1 )
					{
						if( strcmp(player->leftHand.C_String(), "NULL") != 0 )
						{
							oCItem* handItem = (oCItem*)player->npc->GetLeftHand();
							if( handItem )
							{
								player->npc->DoDropVob(handItem);
								handItem->RemoveVobFromWorld();
							}
							handItem = player->npc->CreateItem(zSTRING(player->leftHand.C_String()),1);
							if( handItem )
								player->npc->SetLeftHand(handItem);
						}
						else
						{
							oCItem* handItem = (oCItem*)player->npc->GetLeftHand();
							if( handItem )
							{
								player->npc->DoDropVob(handItem);
								handItem->RemoveVobFromWorld();
							}
						}
					}
					else if( hand == 2 )
					{
						if( strcmp(player->rightHand.C_String(), "NULL") != 0 )
						{
							oCItem* handItem = (oCItem*)player->npc->GetRightHand();
							if( handItem )
							{
								player->npc->DoDropVob(handItem);
								handItem->RemoveVobFromWorld();
							}
							handItem = player->npc->CreateItem(zSTRING(player->rightHand.C_String()),1);
							if( handItem )
								player->npc->SetRightHand(handItem);
						}
						else
						{
							oCItem* handItem = (oCItem*)player->npc->GetRightHand();
							if( handItem )
							{
								player->npc->DoDropVob(handItem);
								handItem->RemoveVobFromWorld();
							}
						}
					}
				}
			}
		}
	}
	
};

void PlayerRPC::SetHealth(BitStream& stream)
{
	DLOG("PlayerRPC::SetHealth()");
	int playerID;
	int hp;
	stream.Read(playerID);
	stream.Read(hp);

	if( core.GetMultiplayer()->GetMyID() != playerID )
	{
		CPlayer* p = playerManager.GetPlayer(playerID);
		if( p )
		{
			if( p->npc )
			{
				p->npc->SetAttribute(NPC_ATR_HITPOINTS, hp);
				p->health = hp;

				if (p->health == 0)
				{
					p->npc->DoDie();
					p->unconscious = false;
					p->dead = true;

					if (p->npc->IsHuman() == 0)
						p->npc->GetModel()->StartAni(zSTRING("T_DEADB"), 0);
				}
				else if (p->dead && p->health > 0)
				{
					p->Respawn();
					p->dead = false;
				}	
			}	
		}
	}
	else
	{
		CPlayer* p = playerManager.GetPlayer(playerID);
		oCNpc* n = oCNpc::GetHero();
		if( p )
		{
			if( n )
			{
				n->SetAttribute(NPC_ATR_HITPOINTS, hp);
				p->health = hp;
				if(p->health == 0)
					n->GetModel()->FadeOutAnisLayerRange(1,2000);

				n->DoDie();

				if(n->GetAttribute(NPC_ATR_HITPOINTS) == 0)
					if(n->IsHuman() == 0)
						n->GetModel()->StartAni(zSTRING("T_DEADB"),0);
			}
		}
	}
};

void PlayerRPC::SetHealthMax(BitStream& stream)
{
	DLOG("PlayerRPC::SetHealthMax()");
	int playerID;
	stream.Read(playerID);

	if( core.GetMultiplayer()->GetMyID() != playerID )
	{
		CPlayer* p = playerManager.GetPlayer(playerID);
		if( p )
		{
			stream.Read(p->maxhealth);
			if( p->npc )
			{
				if( p->maxhealth == 0 )
					p->npc->GetModel()->FadeOutAnisLayerRange(1,2000);
				p->npc->SetAttribute(NPC_ATR_HITPOINTS_MAX, p->maxhealth);

				if(p->npc->GetAttribute(NPC_ATR_HITPOINTS_MAX) == 0)
					if(p->npc->IsHuman() == 0)
						p->npc->GetModel()->StartAni(zSTRING("T_DEADB"),0);
			}	
		}
	}
	else
	{
		CPlayer* p = playerManager.GetPlayer(playerID);
		oCNpc* n = oCNpc::GetHero();
		if( p )
		{
			stream.Read(p->maxhealth);
			if( n )
			{
				if(p->maxhealth == 0)
					n->GetModel()->FadeOutAnisLayerRange(1,2000);
				n->SetAttribute(NPC_ATR_HITPOINTS_MAX, p->maxhealth);
				if(n->GetAttribute(NPC_ATR_HITPOINTS_MAX) == 0)
					if(n->IsHuman() == 0)
						n->GetModel()->StartAni(zSTRING("T_DEADB"),0);
			}
		}
	}
};

void PlayerRPC::AttackHit(BitStream& stream)
{
	DLOG("PlayerRPC::AttackHit()");
	//Tylko w wypadku funkcji "Attack" playerID to zawsze id atakuj¹cego
	int attackID;
	int minushp;
	stream.Read(attackID);
	stream.Read(minushp);

	if(attackID == core.GetMultiplayer()->GetMyID()) return;

	CPlayer* attackPlayer = playerManager.GetPlayer(attackID);
	if( attackPlayer )
	{
		if( attackPlayer->npc )
		{
			oCNpc* hero = oCNpc::GetHero();
			if( hero )
			{
				int health = hero->GetAttribute(NPC_ATR_HITPOINTS);
				if( attackPlayer->npc->GetWeaponMode() != NPC_WEAPON_MAG )
				{
					hero->SetAttribute(NPC_ATR_HITPOINTS, 9999999);
					hero->GetAnictrl()->CreateHit(hero);
				}

				if( (health - minushp) >= 1 )
					hero->SetAttribute(NPC_ATR_HITPOINTS, (health - minushp)); //Nic dalej nie przesy³amy
				else															//CLocalPlayer przechwyci zmianê hp i przeœle j¹ dalej
					hero->SetAttribute(NPC_ATR_HITPOINTS, 1);
			}														
		}
	}
};

void PlayerRPC::AttackDead(BitStream& stream)
{
	DLOG("PlayerRPC::AttackDead()");

	oCNpc* hero = oCNpc::GetHero();

	if (hero)
	{
		hero->SetWeaponMode2(NPC_WEAPON_NONE);
		hero->GetAnictrl()->CreateHit(hero);
		hero->DoDie();

		hero->SetAttribute(NPC_ATR_HITPOINTS, 0);

		if (hero->IsHuman() == 0)
		{
			zCModel* model = hero->GetModel();
			if (model)
			{
				model->FadeOutAnisLayerRange(1, 2000);
				model->StartAni(zSTRING("T_DEADB"), 0);
			}
		}

		playerManager.GetLocalPlayer()->unconscious = false;
	}
};

void PlayerRPC::AttackUnconscious(BitStream& stream)
{
	DLOG("PlayerRPC::AttackUnconscious()");
	int playerID;
	int attackID;
	stream.Read(playerID);
	stream.Read(attackID);
	//Zajebisty stajl mam jo³, takie som realia ¿i¹
	//Strit³er zajebisty najt fajt no³, podnieœ nju ³ere i machaj ni¹
	CPlayer* player = playerManager.GetPlayer(playerID);
	CPlayer* attackPlayer = playerManager.GetPlayer(attackID);
	if( player )
	{
		if( core.GetMultiplayer()->GetMyID() != playerID )
		{
			if( player->npc )
			{
				player->npc->SetWeaponMode2(NPC_WEAPON_NONE);
				player->npc->DropUnconscious(1, oCNpc::GetHero());

				player->unconscious = true;
			}
		}
		else
		{
			oCNpc* hero = oCNpc::GetHero();
			if( hero )
			{
				hero->GetAnictrl()->CreateHit(hero);
				hero->SetWeaponMode2(NPC_WEAPON_NONE);
				hero->DropUnconscious(1, oCNpc::GetHero());

				playerManager.GetLocalPlayer()->unconscious = true;
			}
		}
	}

};

void PlayerRPC::StandUp(BitStream& stream)
{
	DLOG("PlayerRPC::StandUp()");
	int playerID;
	bool unconscious;
	stream.Read(playerID);
	stream.Read(unconscious);
	CPlayer* player = playerManager.GetPlayer(playerID);
	if( player && player->npc )
	{
		if( core.GetMultiplayer()->GetMyID() != playerID )
		{
			if( unconscious == false )
			{
				if( player->npc->IsUnconscious() == 1 )
					player->npc->ForceStandUp();

				player->unconscious = false;
			}
		}
	}
};

void PlayerRPC::MagicSetup(BitStream& stream)
{
	DLOG("PlayerRPC::MagicSetup()");

	int playerID;
	RakString spellInstance;
	stream.Read(playerID);
	stream.Read(spellInstance);

	if( playerID != core.GetMultiplayer()->GetMyID() )
	{
		CPlayer* player = playerManager.GetPlayer(playerID);
		if( player && player->npc )
		{
			if( strcmp(spellInstance.C_String(), "NULL") != 0 )
			{
				DLOG("Spellinstance %s", spellInstance.C_String());
				if( player->spellItem )
				{
					oCMag_Book* book = player->npc->GetSpellBook();
					if( book )
						book->KillSelectedSpell();
					player->npc->DoDropVob(player->spellItem);
					zCWorld* world = oCGame::GetGame()->GetGameWorld();
					if( world )
						world->RemoveVob(player->spellItem);
					player->spellItem = NULL;
				}
				player->spellItem = player->npc->CreateItem(zSTRING(spellInstance.C_String()),1);
				if( player->spellItem )
				{
					player->npc->Equip(player->spellItem);
					oCMag_Book* book = player->npc->GetSpellBook();
					if( book )
						book->Open(0);
				}
			}
			else
			{
				oCMag_Book* book = player->npc->GetSpellBook();
				if( book )
				{
					book->KillSelectedSpell();
				}
				
				if( player->spellItem )
				{
					player->npc->DoDropVob(player->spellItem);
					zCWorld* world = oCGame::GetGame()->GetGameWorld();
					if( world )
						world->RemoveVob(player->spellItem);
					player->spellItem = NULL;
				}
			}
		}
	}
};

void PlayerRPC::MagicAttack(BitStream& stream)
{
	DLOG("PlayerRPC::MagicAttack()");
	int playerID;
	int targetID;
	stream.Read(playerID);
	stream.Read(targetID);

	if( playerID != core.GetMultiplayer()->GetMyID() )
	{
		CPlayer* player = playerManager.GetPlayer(playerID);
		if( player && player->npc )
		{
			if( player->npc->HasMagic() )
			{
				if( player->spellItem )
				{
					if( targetID >= 0 )
					{
						oCMag_Book* book = player->npc->GetSpellBook();
						if( book )
						{
							CPlayer* target = playerManager.GetPlayer(targetID);
							if( targetID != core.GetMultiplayer()->GetMyID() )
							{
								if( target && target->npc )
								{
									player->npc->SetFocusVob(target->npc);
									book->Spell_Setup(player->npc, target->npc);
									book->Spell_Invest();
									book->Spell_Cast();
									CSpell::StartSpellAction(player->npc, target->npc, player->spellItem);
								}
								else
								{
									book->Spell_Setup(player->npc, NULL);
									book->Spell_Invest();
									book->Spell_Cast();
								//	CSpell::StartSpellAction(player->npc, NULL, player->spellItem);
								}
							}
							else
							{
								player->npc->SetFocusVob(oCNpc::GetHero());
								book->Spell_Setup(player->npc, oCNpc::GetHero());
								book->Spell_Invest();
								book->Spell_Cast();
								CSpell::StartSpellAction(player->npc, oCNpc::GetHero(), player->spellItem);
							}

						/*	book->Spell_Invest();
							
							book->Spell_Cast();*/
						}
					}
					else
					{
						zVEC3 pos = player->npc->GetPosition();
						oCNpc* tmp_npc = oCGame::GetGame()->CreateNPC(zSTRING("PC_HERO"),pos.x, pos.y, pos.z);
						if( tmp_npc )
						{
							oCMag_Book* book = player->npc->GetSpellBook();
							if( book )
							{
								player->npc->SetFocusVob(tmp_npc);
								book->Spell_Setup(player->npc,tmp_npc);
								tmp_npc->SetPositionWorld(zVEC3(pos.x+100,pos.y,pos.z));
								book->Spell_Invest();
								book->Spell_Cast();
								CSpell::StartSpellAction(player->npc,tmp_npc,player->spellItem);
								tmp_npc->DestroyNpc();
							}	
						}
					}
				}
			}
		}
	}
};

void PlayerRPC::PlayerList(BitStream& stream) //Lista chuj jebany, jebie liste
{
	char playerList[1024][100];
	memset(&playerList, 1024, 0);
	stream.Read(playerList);
	for( size_t i = 0; i < 1024; ++i )
	{
		CPlayerList::GetInstance().GetList()[i].Clear();
		CPlayerList::GetInstance().GetList()[i] = playerList[i];
	}
};
/*
void PlayerRPC::SetProtection(BitStream& stream)
{
	int playerID, index, value;
	stream.Read(playerID);
	stream.Read(index);
	stream.Read(value);
	CPlayer* player = playerManager.GetPlayer(playerID);
	if (player && player->npc)
	{
		if (core.GetMultiplayer()->GetMyID() != playerID)
		{
			player->npc->SetProtection(index, value);
		}
	}
};
*/
void PlayerRPC::SetOverlay(BitStream& stream)
{
	int playerID;
	bool add;
	RakString overlay;

	stream.Read(playerID);
	stream.Read(add);
	stream.Read(overlay);

	CPlayer* player = playerManager.GetPlayer(playerID);
	if (player && player->npc && core.GetMultiplayer()->GetMyID() != playerID)
	{
		add ? player->npc->ApplyOverlay(zSTRING(overlay.C_String())) : player->npc->RemoveOverlay(zSTRING(overlay.C_String()));
	}
};

void PlayerRPC::MobTrigger(BitStream& stream)
{
	int playerID;
	bool trigger;
	float x, y, z;

	stream.Read(playerID);
	stream.Read(trigger);
	stream.Read(x);
	stream.Read(y);
	stream.Read(z);

	zCTree<zCVob> *tree = oCGame::GetGame()->GetGameWorld()->GetGlobalVobTree().firstChild;
	static oCNpc *staticNpc = oCGame::GetGame()->CreateNPC(zSTRING("PC_HERO"), 0, -1000, 0);
	bool isStatic = false;

	oCNpc *triggerNpc = NULL;
	CPlayer* player = playerManager.GetPlayer(playerID);
	if (player && player->npc && core.GetMultiplayer()->GetMyID() != playerID)
		triggerNpc = player->npc;
	else
	{
		isStatic = true;
		triggerNpc = staticNpc;
	}
		
	while (tree)
	{
		if (tree->data)
		{
			zVEC3 pos = tree->data->GetVobPosition();
			if (goMath::GetDistance3D(x, y, z, pos.x, pos.y, pos.z) < 10)
			{
				if (isStatic) triggerNpc->SetPosition(x, y + 10, z);
				oCMobInter *mob = (oCMobInter*)tree->data;
				switch (::GetVobType(mob))
				{
				case VOB_TYPE_VT_OCMOBSWITCH:
				case VOB_TYPE_VT_OCMOBWHEEL:
				case VOB_TYPE_VT_OCMOBDOOR:
					if (trigger)
					{
						if (!mob->GetS1() && !mob->GetS2())
						{
							mob->StartInteraction(triggerNpc);
							mob->StartStateChange(triggerNpc, 0, 1);
							mob->EndInteraction(triggerNpc, 1);
							mob->OnTrigger(mob, triggerNpc);
							mob->SetState(1, 1);
						}
					}
					else
					{
						if (mob->GetS1() && mob->GetS2())
						{
							mob->StartInteraction(triggerNpc);
							mob->StartStateChange(triggerNpc, 1, 0);
							mob->EndInteraction(triggerNpc, 1);
							mob->OnUntrigger(mob, triggerNpc);
							mob->SetState(0, 0);
						}
					}
					core.GetMultiplayer()->triggerQueue.push(STriggerSync(GetTimeMS() + 1200, triggerNpc, mob));
					break;
				
				case VOB_TYPE_VT_OCMOBINTER:
				case VOB_TYPE_VT_OCMOBCONTAINER:
					if (trigger)
					{
						if (!mob->GetS1() && !mob->GetS2())
						{
							mob->StartInteraction(triggerNpc);
							mob->StartStateChange(triggerNpc, 0, 1);
							mob->EndInteraction(triggerNpc, 1);
							mob->OnTrigger(mob, triggerNpc);
							mob->SetState(1, 1);
						}
					}
					else
					{
						if (mob->GetS1() && mob->GetS2())
						{
							mob->StartInteraction(triggerNpc);
							mob->StartStateChange(triggerNpc, 1, 0);
							mob->EndInteraction(triggerNpc, 1);
							mob->OnUntrigger(mob, triggerNpc);
							mob->SetState(0, 0);
							mob->StopInteraction(triggerNpc);
						}
					}
					break;
				}
			}
		}

		tree = tree->next;
	}

	staticNpc->SetPosition(0, -1000, 0);
}

void PlayerRPC::ShootArrow(BitStream& stream)
{
	int playerID, targetID, aniID, type;

	stream.Read(playerID);
	stream.Read(targetID);
	stream.Read(aniID);
	stream.Read(type);

	if (core.GetMultiplayer()->GetMyID() != playerID)
	{
		CPlayer* player = playerManager.GetPlayer(playerID);
		if (player && player->npc)
		{
			player->npc->SetWeaponMode((oCNpc_WeaponMode)type);

			zCModelAni* animation = player->npc->GetModel()->GetAniFromAniID(aniID);
			if (animation) player->npc->GetModel()->StartAni(animation, 0);

			if (core.GetMultiplayer()->GetMyID() == targetID)
				player->npc->SetFocusVob(oCNpc::GetHero());
			else
			{
				CPlayer* target = playerManager.GetPlayer(targetID);
				if (target && target->npc)
					player->npc->SetFocusVob(target->npc);
			}

			switch (type)
			{
			case NPC_WEAPON_BOW: // Bow arrow
				{
					oCVob *item = player->npc->GetRightHand();
					if (!item)
					{
						oCItem *handItem = player->npc->CreateItem(zSTRING("ITAMARROW"), 1);
						if (handItem)
							player->npc->SetRightHand(handItem);
					}
				}
				break;
			case NPC_WEAPON_CBOW: // Crossbow bolt
				{
					oCVob *item = player->npc->GetLeftHand();
					if (!item)
					{
						oCItem *handItem = player->npc->CreateItem(zSTRING("ITAMBOLT"), 1);
						if (handItem)
							player->npc->SetLeftHand(handItem);
					}
				}
				break;
			}

			player->npc->DoShootArrow(1);
		}
	}
}

void PlayerRPC::ForceStandUp(BitStream& stream)
{
	int playerID, hp;

	stream.Read(playerID);
	stream.Read(hp);

	if (core.GetMultiplayer()->GetMyID() != playerID)
	{
		CPlayer* player = playerManager.GetPlayer(playerID);
		if (player && player->npc)
		{
			player->dead = false;
			if (player->npc->IsUnconscious())
				player->npc->DoDie();

			player->npc->SetAttribute(ATR_HITPOINTS, hp);
		}
	}
}