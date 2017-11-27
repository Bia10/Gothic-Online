#include "stdafx.h"

CLocalPlayer::CLocalPlayer(int playerID, RakString playerName) 
: CPlayer(playerID, playerName)
{
	DLOG("CLocalPlayer::CLocalPlayer()");

	posBroadcastTimer = 0;
	angleBroadcastTimer = 0;
	weaponModeBroadcastTimer = 0;
	armorBroadcastTimer = 0;
	weaponBroadcastTimer = 0;
	instanceBroadcastTimer = 0;
	handBroadcastTimer = 0;
	standUpTimer = 0;
	fightBroadcastTimer = 0;
	worldBroadcastTimer = 0;
	protectionBroadcastTimer = 0;
	skillWeaponBroadcastTimer = 0;
	lastDeathTimer = 0;
	aniBroadcastTimer = 0;
	pingTimer = 0;
	focusTimer = 0;

	isDead = false;
	lastMob = NULL;
};

CLocalPlayer::~CLocalPlayer()
{
	DLOG("CLocalPlayer::~CLocalPlayer()");
};

void CLocalPlayer::SetAdditionalVisuals(zSTRING &_bodyModel, int &_bodyTexture, zSTRING &_headModel, int &_headTexture)
{
	bodyModel = _bodyModel;
	headModel = _headModel;
	bodyTexture = _bodyTexture;
	headTexture = _headTexture;

	if (oCNpc::GetHero()->IsHuman())
	{
		oCNpc::GetHero()->SetAdditionalVisuals(bodyModel, bodyTexture, 1, headModel, headTexture, 0, -1);
	}
}

void CLocalPlayer::Pulse()
{
	this->SendPlayAnimation();
	this->SendPosition();
	this->SendAngle();
	this->SendChangeWeaponMode();
	this->SendWearArmor();
	this->SendEquipWeapon();
	this->SendInstanceChange();
	this->SendHealth();
	this->SendMaxHealth();
	//this->SendHitFocus();
	this->SendStandUp();
	this->SendMagicSetup();
	this->SendHand();
	//this->SendProtection();
	this->BroadcastWorld();
	this->Respawn();
	this->Unconscious();
	this->HandleFocus();
	this->PingSelf();
};

void CLocalPlayer::SendPosition()
{
	zVEC3 playerPos = oCNpc::GetHero()->GetPosition();
	if( posBroadcastTimer < GetTimeMS() )
	{
		int dist = goMath::GetDistance3D(playerPos.x, playerPos.y, playerPos.z, pos.x, pos.y, pos.z);
		if (dist > 25 && core.GetNetwork()->GetPeer()->GetLastPing(core.GetNetwork()->GetServerAddress()) < PING_SYNC_LIMIT)
		{
			BitStream stream;
			stream.Write((MessageID)GO_PLAYER);
			stream.Write((MessageID)SET_POSITION);
			stream.Write(playerPos.x);
			stream.Write(playerPos.y);
			stream.Write(playerPos.z);
			CNetwork* net = core.GetNetwork();
			net->GetPeer()->Send(&stream, LOW_PRIORITY, UNRELIABLE, 0, net->GetServerAddress(), false);

			pos = playerPos;
		}
		else if (dist > 25)
			oCNpc::GetHero()->SetPosition(pos.x, pos.y, pos.z);

		posBroadcastTimer = GetTimeMS() + 200;
	}
};

void CLocalPlayer::SendAngle()
{
	float playerAngle = oCNpc::GetHero()->GetHeading();

	if( angleBroadcastTimer < GetTimeMS() )
	{
		if( playerAngle != angle )
		{
			BitStream stream;
			stream.Write((MessageID)GO_PLAYER);
			stream.Write((MessageID)SET_ROTATION);
			stream.Write(playerAngle);
			CNetwork* net = core.GetNetwork();
			net->GetPeer()->Send(&stream, LOW_PRIORITY, UNRELIABLE, 0, net->GetServerAddress(), false);

			angle = playerAngle;
		}
		angleBroadcastTimer = GetTimeMS() + 160;
	}
};

void CLocalPlayer::SendChangeWeaponMode()
{
	if( weaponModeBroadcastTimer < GetTimeMS() )
	{
		int wm = oCNpc::GetHero()->GetWeaponMode();
		if( wm != this->weaponMode )
		{	
			if( wm != NPC_WEAPON_NONE )
			{
				oCItem* item = reinterpret_cast<oCItem*>(oCNpc::GetHero()->GetLeftHand());
				if( item != NULL && strcmp(item->GetInstanceName().ToChar(), "ITLSTORCHBURNING") == 0 ) //Bug z pochodniami w lapie
				{
					oCNpc::GetHero()->DoDropVob(item);
					item->SetPositionWorld(zVEC3(0, 10000000, 0));
					item->RemoveVobFromWorld();
				}
			}
			DLOG("CLocalPlayer::SendChangeWeaponMode()");
			BitStream stream;
			stream.Write((MessageID)GO_PLAYER);
			stream.Write((MessageID)CHANGE_WEAPONMODE);
			stream.Write(wm);
			CNetwork* net = core.GetNetwork();
			net->GetPeer()->Send(&stream, LOW_PRIORITY, RELIABLE, 0, net->GetServerAddress(), false);
			this->weaponMode = wm;
		}
		weaponModeBroadcastTimer = GetTimeMS() + 300;
	}
};

void CLocalPlayer::SendPlayAnimation()	//Tym razem nie powinno byæ przepe³nienia bufora raknetu
{
	if( aniBroadcastTimer < GetTimeMS() )
	{
		if( playerManager.GetNumberOfPlayers() > 1 )
		{
			oCNpc* hero = oCNpc::GetHero();
			if( hero )
			{
				zCModelAni* ani = hero->GetCurrentAni();
				if( ani )
				{
					int aniID = ani->GetAniID();
					if( this->animationId != aniID )
					{
						BitStream stream;
						stream.Write((MessageID)GO_PLAYER);
						stream.Write((MessageID)PLAY_ANIMATION);
						stream.Write(aniID);
						CNetwork* net = core.GetNetwork();
						net->GetPeer()->Send(&stream, HIGH_PRIORITY, UNRELIABLE, 0, net->GetServerAddress(), false);
						this->animationId = aniID;
					}
				}
			}
		}
		aniBroadcastTimer = GetTimeMS() + 200;
	}
};

void CLocalPlayer::SendWearArmor()
{
	if( armorBroadcastTimer < GetTimeMS() )
	{
		oCNpc* hero = oCNpc::GetHero();
		if( hero )
		{	
			CNetwork* net = core.GetNetwork();
			oCItem* armor = hero->GetEquippedArmor();
			if( armor )
			{
				if (strcmp(armor->GetInstanceName().ToChar(), this->armorInstance.C_String()) != 0) //S¹ ró¿ne
				{
					this->armorInstance = armor->GetInstanceName().ToChar();
					//Wyslanie nowej instancji do serwera
					BitStream stream;
					stream.Write((MessageID)GO_PLAYER);
					stream.Write((MessageID)WEAR_ARMOR);
					stream.Write(this->armorInstance);
					net->GetPeer()->Send(&stream, LOW_PRIORITY, RELIABLE, 0, net->GetServerAddress(), false);
				}

			}
			else //Gdy jest rowne null
			{
				if (strcmp("NULL", this->armorInstance.C_String()) != 0) //S¹ ró¿ne
				{
					//Wyslanie nullwoej instancji do serwera
					this->armorInstance = "NULL";
					BitStream stream;
					stream.Write((MessageID)GO_PLAYER);
					stream.Write((MessageID)WEAR_ARMOR);
					stream.Write(this->armorInstance);
					net->GetPeer()->Send(&stream, LOW_PRIORITY, RELIABLE, 0, net->GetServerAddress(), false);
				}
			}
		}
		armorBroadcastTimer = GetTimeMS() + 1000;
	}
};

void CLocalPlayer::SendEquipWeapon()
{
	if( weaponBroadcastTimer < GetTimeMS() )
	{
		oCNpc* hero = oCNpc::GetHero();
		if( hero )
		{
			CNetwork* net = core.GetNetwork();
			oCItem* meleeWeapon = hero->GetEquippedMeleeWeapon();
			oCItem* rangedWeapon = hero->GetEquippedRangedWeapon();

			if( meleeWeapon )
			{
				if(strcmp(meleeWeapon->GetInstanceName().ToChar(), this->meleeWeaponInstance.C_String()) != 0) //S¹ ró¿ne
				{
					this->meleeWeaponInstance = meleeWeapon->GetInstanceName().ToChar();
					//Wys³anie nowej instancji
					BitStream s1;
					s1.Write((MessageID)GO_PLAYER);
					s1.Write((MessageID)EQUIP_WEAPON);
					s1.Write(1); //1 - melee | 2 - ranged
					s1.Write(this->meleeWeaponInstance);
					net->GetPeer()->Send(&s1, LOW_PRIORITY, RELIABLE, 0, net->GetServerAddress(), false);
				}
			}
			else if( !meleeWeapon )
			{
				if(strcmp(this->meleeWeaponInstance.C_String(), "NULL") != 0 )
				{
					this->meleeWeaponInstance = "NULL";
					BitStream s1;
					s1.Write((MessageID)GO_PLAYER);
					s1.Write((MessageID)EQUIP_WEAPON);
					s1.Write(1); //1 - melee | 2 - ranged
					s1.Write(this->meleeWeaponInstance);
					net->GetPeer()->Send(&s1, LOW_PRIORITY, RELIABLE, 0, net->GetServerAddress(), false);
				}
			}

			if( rangedWeapon )
			{
				if(strcmp(rangedWeapon->GetInstanceName().ToChar(), this->rangedWeaponInstance.C_String()) != 0)
				{
					this->rangedWeaponInstance = rangedWeapon->GetInstanceName().ToChar();
					//Wys³anie nowej instancji
					BitStream s2;
					s2.Write((MessageID)GO_PLAYER);
					s2.Write((MessageID)EQUIP_WEAPON);
					s2.Write(2); //1 - melee | 2 - ranged
					s2.Write(this->rangedWeaponInstance);
					net->GetPeer()->Send(&s2, LOW_PRIORITY, RELIABLE, 0, net->GetServerAddress(), false);
				}
			}
			else if( !rangedWeapon )
			{
				if(strcmp(this->rangedWeaponInstance.C_String(), "NULL") != 0)
				{
					this->rangedWeaponInstance = "NULL";
					//Wys³anie nowej instancji
					BitStream s2;
					s2.Write((MessageID)GO_PLAYER);
					s2.Write((MessageID)EQUIP_WEAPON);
					s2.Write(2); //1 - melee | 2 - ranged
					s2.Write(this->rangedWeaponInstance);
					net->GetPeer()->Send(&s2, LOW_PRIORITY, RELIABLE, 0, net->GetServerAddress(), false);		
				}
			}
		}

		weaponBroadcastTimer = GetTimeMS() + 1000;
	}
};

void CLocalPlayer::SendInstanceChange()
{
	if( instanceBroadcastTimer < GetTimeMS() )
	{
		oCNpc* hero = oCNpc::GetHero();
		if( hero )
		{
			CNetwork* net = core.GetNetwork();
			zSTRING instance = hero->GetInstanceName();
			if( strcmp(instance.ToChar(), this->instance.C_String()) != 0 )
			{
				DLOG("CLocalPlayer::SendInstanceChange()");
				this->instance = instance.ToChar();

				BitStream stream;
				stream.Write((MessageID)GO_PLAYER);
				stream.Write((MessageID)CHANGE_INSTANCE);
				stream.Write(this->instance);
				net->GetPeer()->Send(&stream, LOW_PRIORITY, RELIABLE, 0, net->GetServerAddress(), false);
				
				instanceBroadcastTimer = GetTimeMS() + 3000; //co 5 sekund xd | OK, ale lepiej co 3 xD
			}
		}
	}
};

void CLocalPlayer::SendHand()
{
	if( this->handBroadcastTimer < GetTimeMS() )
	{
		oCNpc* hero = oCNpc::GetHero();
		if( hero )
		{
			CNetwork* net = core.GetNetwork();
			oCItem* leftHandIt = (oCItem*)hero->GetLeftHand();
			oCItem* rightHandIt = (oCItem*)hero->GetRightHand();
			if( leftHandIt )
			{
				if( strcmp(this->leftHand.C_String(), leftHandIt->GetInstanceName().ToChar()) != 0 )
				{
					this->leftHand = leftHandIt->GetInstanceName().ToChar();
					//core.GetChat()->AddLine(RakString("L+ %s", this->leftHand.C_String()), zCOLOR(255, 0, 0));
					DLOG("Left hand: %s",this->leftHand.C_String());
					SCallback::onUseItem(leftHand.C_String(), leftHandIt->GetAmount(), 0);

					BitStream stream;
					stream.Write((MessageID)GO_PLAYER);
					stream.Write((MessageID)ITEM_HAND);
					stream.Write(1); //Left hand
					stream.Write(this->leftHand);

					net->GetPeer()->Send(&stream, LOW_PRIORITY, RELIABLE, 0, net->GetServerAddress(), false);
				}
			}
			else if( !leftHandIt )
			{
				if( strcmp(this->leftHand.C_String(), "NULL") != 0 )
				{
					this->leftHand = "NULL";
					//core.GetChat()->AddLine(RakString("L- %s", this->leftHand.C_String()), zCOLOR(255, 0, 0));
					DLOG("Left hand: %s",this->leftHand.C_String());
					SCallback::onUseItem("NULL", 0, 0);

					BitStream stream;
					stream.Write((MessageID)GO_PLAYER);
					stream.Write((MessageID)ITEM_HAND);
					stream.Write(1);
					stream.Write(this->leftHand);

					net->GetPeer()->Send(&stream, LOW_PRIORITY, RELIABLE, 0, net->GetServerAddress(), false);
				}
			}
			if( rightHandIt )
			{
				if( strcmp(this->rightHand.C_String(), rightHandIt->GetInstanceName().ToChar()) != 0 )
				{
					this->rightHand = rightHandIt->GetInstanceName().ToChar();
					//core.GetChat()->AddLine(RakString("R+ %s", this->rightHand.C_String()), zCOLOR(255, 0, 0));
					DLOG("Right hand:%s", this->rightHand.C_String());
					SCallback::onUseItem(rightHand.C_String(), rightHandIt->GetAmount(), 1);

					BitStream stream;
					stream.Write((MessageID)GO_PLAYER);
					stream.Write((MessageID)ITEM_HAND);
					stream.Write(2);
					stream.Write(this->rightHand);

					net->GetPeer()->Send(&stream, LOW_PRIORITY, RELIABLE, 0, net->GetServerAddress(), false);
				}
			}
			else if( !rightHandIt )
			{
				if( strcmp(this->rightHand.C_String(), "NULL") != 0 )
				{
					this->rightHand = "NULL";
					//core.GetChat()->AddLine(RakString("R- %s", this->rightHand.C_String()), zCOLOR(255, 0, 0));
					DLOG("Right hand:%s", this->rightHand.C_String());
					SCallback::onUseItem("NULL", 0, 1);

					BitStream stream;
					stream.Write((MessageID)GO_PLAYER);
					stream.Write((MessageID)ITEM_HAND);
					stream.Write(2);
					stream.Write(this->rightHand);
					net->GetPeer()->Send(&stream, LOW_PRIORITY, RELIABLE, 0, net->GetServerAddress(), false);

				}
			}
		}
		this->handBroadcastTimer = GetTimeMS() + 700;
	}
};

void CLocalPlayer::SendChangeLevel(RakString levelName)
{
	//Brak timera bo zmian¹ worldu nie da sie spamowac
	this->world = levelName;
	BitStream s;
	s.Write((MessageID)GO_PLAYER);
	s.Write((MessageID)CHANGE_LEVEL);
	s.Write(this->world);

	CNetwork* n = core.GetNetwork();	//Ustawilem unreliable, bo watek odbierajacy pakiety w tym momencie jest nieaktywny
	n->GetPeer()->Send(&s, LOW_PRIORITY, UNRELIABLE, 0, n->GetServerAddress(), false);
};

void CLocalPlayer::SendEnterWorld()
{
	//Brak timera
	BitStream s;
	s.Write((MessageID)GO_PLAYER);
	s.Write((MessageID)ENTER_WORLD);

	CNetwork* n = core.GetNetwork(); //Jak bedzie gubic pakiety to ustawic na RELIABLE_OREDERED
	n->GetPeer()->Send(&s, LOW_PRIORITY, UNRELIABLE, 0, n->GetServerAddress(), false);
};

void CLocalPlayer::SendHealth()
{
	oCNpc* hero = oCNpc::GetHero();
	if( hero )
	{
		if( hero->GetAttribute(NPC_ATR_HITPOINTS) != this->health )
		{
			BitStream stream;
			stream.Write((MessageID)GO_PLAYER);
			stream.Write((MessageID)SET_HEALTH);
			stream.Write(hero->GetAttribute(NPC_ATR_HITPOINTS));

			CNetwork* net = core.GetNetwork();
			net->GetPeer()->Send(&stream, HIGH_PRIORITY, RELIABLE, 0, net->GetServerAddress(), false);

			this->health = hero->GetAttribute(NPC_ATR_HITPOINTS);
		}
	}
};

void CLocalPlayer::SendMaxHealth()
{
	oCNpc* hero = oCNpc::GetHero();
	if( hero )
	{
		if( hero->GetAttribute(NPC_ATR_HITPOINTS_MAX) != this->maxhealth )
		{
			BitStream stream;
			stream.Write((MessageID)GO_PLAYER);
			stream.Write((MessageID)SET_HEALTH_MAX);
			stream.Write(hero->GetAttribute(NPC_ATR_HITPOINTS_MAX));

			CNetwork* net = core.GetNetwork();
			net->GetPeer()->Send(&stream, LOW_PRIORITY, RELIABLE, 0, net->GetServerAddress(), false);

			this->maxhealth = hero->GetAttribute(NPC_ATR_HITPOINTS_MAX);
		}
	}
};

void CLocalPlayer::SendHitFocus(oCNpc *target)
{
	oCNpc* hero = oCNpc::GetHero();
	if (hero)
	{
		CNetwork* net = core.GetNetwork();
		CPlayer* focusPlayer = playerManager.GetPlayer(target);
		if (focusPlayer && net->GetPeer()->GetLastPing(core.GetNetwork()->GetServerAddress()) < PING_SYNC_LIMIT)
		{
			if (target->GetAttribute(NPC_ATR_HITPOINTS) < focusPlayer->health)
			{
				//Obliczanie ilosci hp do odjêcia
				int minushp = (focusPlayer->health - target->GetAttribute(NPC_ATR_HITPOINTS));
				if ((focusPlayer->health - minushp) == 1)
					minushp = 0;

				if (hero->GetWeaponMode() != NPC_WEAPON_NONE)
				{
						if (!target->IsDead())
						{
							if (!target->IsUnconscious() && minushp > 0)
							{
								SCallback::onHit();

								BitStream stream;
								stream.Write((MessageID)GO_PLAYER);
								stream.Write((MessageID)ATTACK_HIT);
								stream.Write(focusPlayer->GetID());
								stream.Write(minushp);

								net->GetPeer()->Send(&stream, HIGH_PRIORITY, RELIABLE, 0, net->GetServerAddress(), false);

								focusPlayer->health = target->GetAttribute(NPC_ATR_HITPOINTS);
							}
							else if (!hero->IsHuman() || !target->IsHuman())
							{
								BitStream stream;
								stream.Write((MessageID)GO_PLAYER);
								stream.Write((MessageID)ATTACK_DEAD);
								stream.Write(focusPlayer->GetID());

								net->GetPeer()->Send(&stream, MEDIUM_PRIORITY, RELIABLE, 0, net->GetServerAddress(), false);
								if (target->IsUnconscious())
									target->DoDie();

								focusPlayer->unconscious = false;
							}
							else if (!focusPlayer->unconscious)
							{
								BitStream stream;
								stream.Write((MessageID)GO_PLAYER);
								stream.Write((MessageID)ATTACK_UNCONSCIOUS);
								stream.Write(focusPlayer->GetID());

								net->GetPeer()->Send(&stream, MEDIUM_PRIORITY, RELIABLE, 0, net->GetServerAddress(), false);
								focusPlayer->unconscious = true;
							}
						}
						else
						{
							BitStream stream;
							stream.Write((MessageID)GO_PLAYER);
							stream.Write((MessageID)ATTACK_DEAD);
							stream.Write(focusPlayer->GetID());

							net->GetPeer()->Send(&stream, MEDIUM_PRIORITY, RELIABLE, 0, net->GetServerAddress(), false);

							if (target->IsUnconscious())
								target->DoDie();

							focusPlayer->unconscious = false;
						}
				}
			}
			else if (focusPlayer->npc->IsUnconscious() && focusPlayer->unconscious == false)
			{
				BitStream stream;
				stream.Write((MessageID)GO_PLAYER);
				stream.Write((MessageID)ATTACK_UNCONSCIOUS);
				stream.Write(focusPlayer->GetID());

				net->GetPeer()->Send(&stream, MEDIUM_PRIORITY, RELIABLE, 0, net->GetServerAddress(), false);
				focusPlayer->unconscious = true;
			}
		}
	}
};

void CLocalPlayer::SendStandUp()
{
	if( this->standUpTimer < GetTimeMS() )
	{
		oCNpc* hero = oCNpc::GetHero();
		if( hero )
		{
			if( this->unconscious == true )
			{
				if( hero->IsUnconscious() == 0 )
				{
					this->unconscious = false;
					SCallback::onStandUp();

					//Wys³anie ¿e wstaje
					BitStream stream;
					stream.Write((MessageID)GO_PLAYER);
					stream.Write((MessageID)STAND_UP);
					stream.Write(false); //¯e wstaje, true - ¿e pada
					core.GetNetwork()->GetPeer()->Send(&stream, LOW_PRIORITY, RELIABLE, 0, core.GetNetwork()->GetServerAddress(), false);
				}
			}
			else
			{
				if( hero->IsUnconscious() == 1 )
				{
					//Standup na false, pada. ale tego raczej nie bedziemy robic
					this->unconscious = true;
				}
			}
		}
		this->standUpTimer = GetTimeMS() + 1000;
	}
};

void CLocalPlayer::SendMagicSetup()
{							
	oCNpc* hero = oCNpc::GetHero();
	if( !hero ) return;
	if( hero->GetWeaponMode() == NPC_WEAPON_MAG )
	{
		oCMag_Book* book = hero->GetSpellBook();
		if( book )
		{
			int mag_spellID = book->GetSelectedSpellNr();
			if( this->spellID != mag_spellID )
			{
				oCItem* item = book->GetSpellItem(mag_spellID);
				if( item )
				{	
					//Bo buguje gre
					if(strcmp(item->GetInstanceName().ToChar(), "ITARRUNECONTROL") == 0)
					{
						hero->SetWeaponMode2(NPC_WEAPON_NONE);
						hero->DoDropVob(item);
						item->RemoveVobFromWorld();
						return;
					} //Wymuszone usuniêcie spela
					BitStream stream;
					stream.Write((MessageID)GO_PLAYER);
					stream.Write((MessageID)MAGIC_SETUP);
					stream.Write(RakString(item->GetInstanceName().ToChar()));
					CNetwork* net = core.GetNetwork();
					net->GetPeer()->Send(&stream,LOW_PRIORITY,RELIABLE,0,net->GetServerAddress(), false);
					//Wys³anie
					this->spellID = mag_spellID;
				}
			}
		}
	}
	else
	{
		if( this->spellID >= 0 )
		{
			//Wys³anie null
			BitStream stream;
			stream.Write((MessageID)GO_PLAYER);
			stream.Write((MessageID)MAGIC_SETUP);
			stream.Write(RakString("NULL"));
			CNetwork* net = core.GetNetwork();
			net->GetPeer()->Send(&stream,LOW_PRIORITY,RELIABLE,0,net->GetServerAddress(), false);
			//Wys³anie
			this->spellID = -1;
		}
	}
};

void CLocalPlayer::SendMagicAttack()
{
	oCNpc* hero = oCNpc::GetHero();
	if( hero )
	{
		oCNpc* focus = hero->GetFocusNpc();
		if( focus )
		{
			CPlayer* focusPlayer = playerManager.GetPlayer(focus);
			if( focusPlayer )
			{
				BitStream stream;
				stream.Write((MessageID)GO_PLAYER);
				stream.Write((MessageID)MAGIC_ATTACK);
				stream.Write(focusPlayer->GetID());
				CNetwork* net = core.GetNetwork();
				net->GetPeer()->Send(&stream,LOW_PRIORITY,UNRELIABLE,0,net->GetServerAddress(),false);
			}
			else
			{
				//brak celu
				BitStream stream;
				stream.Write((MessageID)GO_PLAYER);
				stream.Write((MessageID)MAGIC_ATTACK);
				stream.Write(-1);
				CNetwork* net = core.GetNetwork();
				net->GetPeer()->Send(&stream,LOW_PRIORITY,UNRELIABLE,0,net->GetServerAddress(),false);
			}
		}
		else
		{
			//brak celu
			BitStream stream;
			stream.Write((MessageID)GO_PLAYER);
			stream.Write((MessageID)MAGIC_ATTACK);
			stream.Write(-1);
			CNetwork* net = core.GetNetwork();
			net->GetPeer()->Send(&stream,LOW_PRIORITY,UNRELIABLE,0,net->GetServerAddress(),false);
		}
	}
};

void CLocalPlayer::SendOverlay(bool add, RakString overlay)
{
	if (overlay != "HUMANS_TORCH.MDS")
	{
		BitStream stream;
		stream.Write((MessageID)GO_PLAYER);
		stream.Write((MessageID)SET_OVERLAY);
		stream.Write(add);
		stream.Write(overlay);

		core.GetNetwork()->GetPeer()->Send(&stream, LOW_PRIORITY, RELIABLE, 0, core.GetNetwork()->GetServerAddress(), false);
	}
}

void CLocalPlayer::SendTimedOverlay(TimeMS time, RakString overlay)
{
	BitStream stream;
	stream.Write((MessageID)GO_PLAYER);
	stream.Write((MessageID)SET_TIMED_OVERLAY);
	stream.Write(time);
	stream.Write(overlay);

	core.GetNetwork()->GetPeer()->Send(&stream, LOW_PRIORITY, RELIABLE, 0, core.GetNetwork()->GetServerAddress(), false);
}

void CLocalPlayer::SendMobTrigger(bool trigger, oCMobInter *mob)
{
	zVEC3 pos = mob->GetVobPosition();

	BitStream stream;
	stream.Write((MessageID)GO_PLAYER);
	stream.Write((MessageID)MOB_TRIGGER);
	stream.Write(trigger);
	stream.Write(this->world);
	stream.Write(pos.x);
	stream.Write(pos.y);
	stream.Write(pos.z);

	core.GetNetwork()->GetPeer()->Send(&stream, MEDIUM_PRIORITY, RELIABLE, 0, core.GetNetwork()->GetServerAddress(), false);
}

void CLocalPlayer::SendArrow()
{
	int targetID = -1;
	int aniID, type;

	oCNpc *hero = oCNpc::GetHero();
	oCNpc *focus = hero->GetFocusNpc();

	if (focus)
	{
		CPlayer *focusPlayer = playerManager.GetPlayer(focus);
		if (focusPlayer)
			targetID = focusPlayer->GetID();
	}

	aniID = hero->GetAnimationID();
	type = hero->GetWeaponMode();

	BitStream stream;
	stream.Write((MessageID)GO_PLAYER);
	stream.Write((MessageID)SHOOT_ARROW);
	stream.Write(targetID);
	stream.Write(aniID);
	stream.Write(type);

	core.GetNetwork()->GetPeer()->Send(&stream, HIGH_PRIORITY, RELIABLE, 0, core.GetNetwork()->GetServerAddress(), false);
}

void CLocalPlayer::SendFocus(int playerID, int focusID, bool taken)
{
	BitStream stream;
	stream.Write((MessageID)GO_SCRIPT);
	stream.Write((MessageID)SCRIPT_FOCUS);
	stream.Write(taken);
	stream.Write(playerID);
	stream.Write(focusID);

	core.GetNetwork()->GetPeer()->Send(&stream, LOW_PRIORITY, RELIABLE, 0, core.GetNetwork()->GetServerAddress(), false);
}
/*
void CLocalPlayer::SendProtection()
{
	if (this->protectionBroadcastTimer < GetTimeMS())
	{
		oCNpc *hero = oCNpc::GetHero();
		
		int protWeapon = hero->GetProtection(PROT_WEAPON);
		int protArrow = hero->GetProtection(PROT_ARROW);
		int protFire = hero->GetProtection(PROT_FIRE);
		int protMagic = hero->GetProtection(PROT_MAGIC);

		CNetwork* net = core.GetNetwork();

		if (protWeapon != protection[0])
		{
			BitStream stream;
			stream.Write((MessageID)GO_PLAYER);
			stream.Write((MessageID)SET_PROTECTION);
			stream.Write(0);
			stream.Write(protWeapon);
			
			net->GetPeer()->Send(&stream, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, net->GetServerAddress(), false);

			protection[0] = protWeapon;
		}

		if (protArrow != protection[1])
		{
			BitStream stream;
			stream.Write((MessageID)GO_PLAYER);
			stream.Write((MessageID)SET_PROTECTION);
			stream.Write(1);
			stream.Write(protArrow);

			net->GetPeer()->Send(&stream, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, net->GetServerAddress(), false);

			protection[1] = protArrow;
		}

		if (protFire != protection[2])
		{
			BitStream stream;
			stream.Write((MessageID)GO_PLAYER);
			stream.Write((MessageID)SET_PROTECTION);
			stream.Write(2);
			stream.Write(protFire);

			net->GetPeer()->Send(&stream, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, net->GetServerAddress(), false);

			protection[2] = protFire;
		}

		if (protMagic != protection[3])
		{
			BitStream stream;
			stream.Write((MessageID)GO_PLAYER);
			stream.Write((MessageID)SET_PROTECTION);
			stream.Write(3);
			stream.Write(protMagic);

			net->GetPeer()->Send(&stream, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, net->GetServerAddress(), false);

			protection[3] = protMagic;
		}

		this->protectionBroadcastTimer = GetTimeMS() + 1200;
	}
};
*/

void CLocalPlayer::BroadcastWorld()
{
	if( this->worldBroadcastTimer < GetTimeMS() )
	{
		zCWorld* zworld = oCGame::GetGame()->GetGameWorld();
		RakString worldName = RakString("%s.ZEN", zworld->GetWorldName().ToChar());
		if( zworld )
		{
			if( strcmp(this->world.C_String(), worldName.C_String()) != 0 )
			{
				playerManager.DestroyAllPlayers();
				this->SendChangeLevel(worldName);
				this->SendEnterWorld();
			}
		}
		worldName.FreeMemory();
		this->worldBroadcastTimer = GetTimeMS() + 800;
	}
};

void CLocalPlayer::Respawn()
{
	if( lastDeathTimer < GetTimeMS() )
	{
		oCNpc* hero = oCNpc::GetHero();
		if( hero->IsDead() )
		{
			if( isDead == false )
			{
				lastDeathTimer = GetTimeMS() + 5000;
				isDead = true;
				
				SCallback::onDie();

				if (hero->IsHuman())
				{
					// Unequip weapons
					oCItem *meleeWeapon = hero->GetEquippedMeleeWeapon();
					if (meleeWeapon) hero->UnequipItem(meleeWeapon);
					oCItem *rangedWeapon = hero->GetEquippedRangedWeapon();
					if (rangedWeapon) hero->UnequipItem(rangedWeapon);

					oCItem* leftHand = (oCItem*)hero->GetLeftHand();
					if (leftHand)
					{
						hero->DoDropVob(leftHand);

						int amount = leftHand->GetAmount();
						zSTRING instance = leftHand->GetInstanceName();

						leftHand->RemoveVobFromWorld();
						hero->CreateItem(instance, amount);
					}
					oCItem* rightHand = (oCItem*)hero->GetRightHand();
					if (rightHand)
					{
						hero->DoDropVob(rightHand);

						int amount = rightHand->GetAmount();
						zSTRING instance = rightHand->GetInstanceName();

						rightHand->RemoveVobFromWorld();
						hero->CreateItem(instance, amount);
					}
				}

				return;
			}
			else
			{
				zVEC3 pos = oCGame::GetGame()->GetStartPos();
				hero->SetAttribute(NPC_ATR_HITPOINTS, 1);
				hero->SetPosition(pos.x, pos.y+15, pos.z);
				hero->ForceStandUp();
				hero->GetModel()->FadeOutAnisLayerRange(1, 2000);
				isDead = false;
				unconscious = false;

				oCGame* game = oCGame::GetGame();
				if (game->GetShowPlayerStatus())
				{
					game->SetShowPlayerStatus(0);
					game->SetShowPlayerStatus(1);
				}

				SCallback::onRespawn();
			}
		}
		else
			isDead = false;
		lastDeathTimer = GetTimeMS() + 300;
	}
};

void CLocalPlayer::Unconscious()
{
	if (oCNpc::GetHero()->IsUnconscious() && !this->unconscious && scr.GetScriptVars()->isUnconsciousEnabled)
	{
		this->unconscious = true;
		SCallback::onUnconscious();
	}
}

void CLocalPlayer::ReleaseMob()
{
	if (lastMob)
	{
		oCNpc *hero = oCNpc::GetHero();

		zVEC3 posMob = lastMob->GetVobPosition();
		zVEC3 posHero = hero->GetPosition();

		if (goMath::GetDistance3D(posMob.x, posMob.y, posMob.z, posHero.x, posHero.y, posHero.z) < 150)
		{
			SendMobTrigger(false, lastMob);
			lastMob->SendStateChange(1, 0);
			lastMob->EndInteraction(hero, 1);
			lastMob->SetState(1, 0);
			lastMob->Hook_OnUntrigger(lastMob, hero);
		}
		lastMob = NULL;
	}
}

void CLocalPlayer::HandleFocus()
{
	static oCNpc *hasFocus = NULL;
	static zSTRING focusName = "";
	static int focusID = -1;

	if (focusTimer < GetTimeMS())
	{
		oCNpc *focus = oCNpc::GetHero()->GetFocusNpc();
		if (focus)
		{
			if (hasFocus && focus && hasFocus != focus)
			{
				hasFocus = focus;

				SCallback::onLostFocus(focusID, focusName.ToChar());
				SendFocus(this->id, focusID, false);

				zVEC3 pos = focus->GetPosition();
				CPlayer *player = playerManager.GetPlayer(focus);

				focusID = player ? player->GetID() : -1;

				SCallback::onTakeFocus(focusID, focus->GetName(0).ToChar(), pos.x, pos.y, pos.z);
				SendFocus(this->id, focusID, true);
			}
			else if (!hasFocus)
			{
				hasFocus = focus;

				zVEC3 pos = focus->GetPosition();
				CPlayer *player = playerManager.GetPlayer(focus);
				
				focusID = player ? player->GetID() : -1;

				SCallback::onTakeFocus(focusID, focus->GetName(0).ToChar(), pos.x, pos.y, pos.z);
				SendFocus(this->id, focusID, true);
			}

			focusName = focus->GetName(0);
		}
		else if (hasFocus)
		{
			hasFocus = NULL;
			SCallback::onLostFocus(focusID, focusName.ToChar());
		}

		focusTimer = GetTimeMS() + 50;
	}
}

void CLocalPlayer::PingSelf()
{
	if( pingTimer < GetTimeMS() )
	{
		core.GetNetwork()->GetPeer()->Ping(core.GetNetwork()->GetServerAddress());
		pingTimer = GetTimeMS() + 3000;
	}
};