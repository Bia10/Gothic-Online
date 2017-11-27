#include "stdafx.h"

CPlayer::CPlayer()
{
	DLOG("CPlayer::CPlayer()");

	isSlideAllowed = false;
	timerSlide = 0;
	timerArmor = 0;
	timerWeapon = 0;
	timerHealth = 0;
};

CPlayer::CPlayer(int playerID, RakString playerName)
{
	DLOG("CPlayer::CPlayer(%d, %s)",playerID,playerName.C_String());

	id = playerID;
	name = playerName;

	isSlideAllowed = false;
	timerSlide = 0;
	timerArmor = 0;
	timerWeapon = 0;
	timerHealth = 0;
};

CPlayer::~CPlayer()
{
	DLOG("CPlayer::~CPlayer() ID = %d",this->id);

	if( this->npc )
	{
		this->npc->DestroyNpc();
		this->npc = NULL;
	}
};

void CPlayer::Spawn(float x, float y, float z, RakString instance)
{
	DLOG("CPlayer::Spawn(%f, %f, %f)", x, y, z);

	if( this->npc == NULL )
	{
		this->instance = instance;
		this->npc = oCGame::GetGame()->CreateNPC(zSTRING(instance.C_String()), this->pos.x, this->pos.y, this->pos.z);
		//Sprawdzenie czy nie jest botem
		if( this->npc->IsMonster() || this->npc->IsGoblin() || this->npc->IsHalfMonster() ) //Sprawdzenie czy nie jest zdolny do auto ataku xd
			this->npc->SetAI(NULL); //Po takim zabiegu niestety animki scinaja
		this->npc->SetName(zSTRING(RakString("%s (%d)", this->name.C_String(), this->GetID()).C_String()));

	}
};

void CPlayer::Respawn()
{
	DLOG("CPlayer::Respawn()");
	if( this->npc )
	{
		// Old creating new NPC :)
		/*oCNpc* old_npc = this->npc;
		oCNpc* new_npc = oCGame::GetGame()->CreateNPC(zSTRING(this->instance.C_String()), 0, -3000, 0);
		if( new_npc )
		{
			this->npc = new_npc;
			this->npc->SetAttribute(NPC_ATR_HITPOINTS_MAX, this->maxhealth);
			this->npc->SetName(zSTRING(RakString("%s (%d)", this->name.C_String(), this->GetID()).C_String()));
			//Ubieranie zbroi i broni (w CRepair)
			old_npc->DestroyNpc();
		}*/
		this->pos.x = 0; this->pos.y = -3000; this->pos.z = 0;
		this->npc->SetPosition(0, -3000, 0);
		this->npc->StopFaceAni(zSTRING("T_HURT"));
		this->npc->SetCollDet(true);
	}
	else
	{
		this->npc = oCGame::GetGame()->CreateNPC(zSTRING(this->instance.C_String()), 0, -3000, 0);
		this->npc->SetAttribute(NPC_ATR_HITPOINTS_MAX, this->maxhealth);
		this->npc->SetName(zSTRING(RakString("%s (%d)", this->name.C_String(), this->GetID()).C_String()));
		//Ubieranie zbroi i broni (w CRepair)
	}
};

void CPlayer::UnSpawn()
{
	DLOG("CPlayer::UnSpawn() ID = %d", this->GetID());
	if( this->npc )
	{
		this->npc->DestroyNpc();
		this->npc = NULL;
	}
};

void CPlayer::SetAdditionalVisuals(zSTRING &_bodyModel, int &_bodyTexture, zSTRING &_headModel, int &_headTexture)
{
	bodyModel = _bodyModel;
	headModel = _headModel;
	bodyTexture = _bodyTexture;
	headTexture = _headTexture;
	
	if (this->npc && this->npc->IsHuman())
	{
		this->npc->SetAdditionalVisuals(bodyModel, bodyTexture, 1, headModel, headTexture, 0, -1);
	}
}

void CPlayer::Repair()
{
	if( this->npc )
	{
		RefreshPositions();
		RefreshAngle();
		RefreshArmor();
		RefreshHealth();
		RefreshWeapon();
		RefreshWeaponMode();
		RefreshTemporaryAnimation();
	}
};

void CPlayer::RefreshTemporaryAnimation()
{
	zCModel* model = npc->GetModel();
	if( model )
	{
		zCModelAni* ani = model->GetAniFromAniID(animationId);
		if( ani )
		{
			if( ani->GetAniName().ToChar()[0] == 'T' )
				model->StartAni(animationId, 0);
		}
	}
};

void CPlayer::RefreshPositions()
{
	if( GetTimeMS() < timerSlide )
	{
		if( isSlideAllowed )
		{
			if( npc )
			{
				if (!dead && npc->GetAttribute(NPC_ATR_HITPOINTS) > 0 && npc->IsUnconscious() == 0)
				{
					zVEC3 _pos = npc->GetPosition();

					float distance2d = goMath::GetDistance2D(_pos.x, _pos.z, pos.x, pos.z);
					float distance3d = goMath::GetDistance3D(_pos.x, _pos.y, _pos.z, pos.x, pos.y, pos.z);

					if( distance2d >= 1 && distance3d < 200 )
					{
						float _angle = goMath::GetVectorAngle(_pos.x, _pos.z, pos.x, pos.z);
						_pos.x += sin(_angle * 3.14f / 180.0f) * (distance3d / 15);
						_pos.z += cos(_angle * 3.14f / 180.0f) * (distance3d / 15);

						if(pos.y > _pos.y)
							_pos.y += (distance3d / 30);
						else if(pos.y < _pos.y)
							_pos.y -= (distance3d / 30);

						npc->SetPosition(_pos.x, _pos.y, _pos.z);
					}
					else if (distance3d >= 200)
						npc->SetPosition(pos.x, pos.y, pos.z);
				}
			}
		}
	}
	else if( GetTimeMS() > timerSlide )
	{
		if( isSlideAllowed == false )
		{
			isSlideAllowed = true;
			timerSlide = GetTimeMS() + 1000; //Œlizg
		}
		else
		{
			isSlideAllowed = false;
			timerSlide = GetTimeMS() + 300; //Przerwa
		}
	}
};

void CPlayer::RefreshAngle()
{
	if(npc->GetAttribute(NPC_ATR_HITPOINTS) > 0 && npc->IsUnconscious() == 0 && angle != npc->GetHeading())
    {
		npc->SetHeading( angle );
	}
};

void CPlayer::RefreshArmor()
{
	if( GetTimeMS() > timerArmor )
	{
		if( npc->GetAttribute(NPC_ATR_HITPOINTS) > 0 && npc->IsUnconscious() == 0 && npc->IsHuman() == 1 )
		{
			oCItem* armor = npc->GetEquippedArmor();
			if( armor )
			{
				if(strcmp(armorInstance.C_String(), armor->GetInstanceName().ToChar()) != 0)
				{
					if(strcmp(armorInstance.C_String(), "NULL") == 0)
					{
						DLOG("Remove armor");
						npc->UnequipItem(armor);
						npc->DoDropVob(armor);
						armor->RemoveVobFromWorld();
					}
					else
					{
						DLOG("Equip armor");
						npc->UnequipItem(armor);
						npc->DoDropVob(armor);
						armor->RemoveVobFromWorld();
						armor = npc->CreateItem(zSTRING(armorInstance.C_String()), 1);
						if(armor)
							npc->Equip(armor);
					}
				}
			}
			else if( !armor )
			{
				if(strcmp(armorInstance.C_String(), "NULL") != 0)
				{
					DLOG("Equip armor");
					armor = npc->CreateItem(zSTRING(armorInstance.C_String()), 1);
					if(armor)
						npc->Equip(armor);
				}
			}
		}
		timerArmor = GetTimeMS() + 3000;
	}
};

void CPlayer::RefreshHealth()
{
	if( GetTimeMS() > timerHealth )
	{
		if( health > 0 )
		{
			if( health != npc->GetAttribute(NPC_ATR_HITPOINTS) )
			{
				npc->SetAttribute(NPC_ATR_HITPOINTS,health);
			}
		}
		else
		{
			if( health != npc->GetAttribute(NPC_ATR_HITPOINTS) )
			{
				if( !npc->IsDead() )
					npc->DoDie();
				npc->SetAttribute(NPC_ATR_HITPOINTS,health);
			}
		}
		timerHealth = GetTimeMS() + 1200;
	}
};

void CPlayer::RefreshWeapon()
{
	if( GetTimeMS() > timerWeapon )
	{
		if (npc->GetAttribute(NPC_ATR_HITPOINTS) > 0 && !npc->IsUnconscious() && npc->IsHuman() == 1)
		{
			if( npc->GetWeaponMode() != NPC_WEAPON_1HS && npc->GetWeaponMode() != NPC_WEAPON_2HS )
			{
				oCItem* melee = npc->GetEquippedMeleeWeapon();
				if( melee )
				{
					if( strcmp(meleeWeaponInstance.C_String(), "NULL") == 0 )
					{
						npc->UnequipItem(melee);
					}
					else if( strcmp(meleeWeaponInstance.C_String(), melee->GetInstanceName().ToChar()) != 0 )
					{
						npc->UnequipItem(melee);
						oCItem* new_melee = npc->CreateItem(zSTRING(meleeWeaponInstance.C_String()), 1);
						if( new_melee )
						{
							npc->Equip(new_melee);
						}
					}
				}
				else
				{
					if( strcmp( meleeWeaponInstance.C_String(), "NULL") != 0 )
					{
						oCItem* new_melee = npc->CreateItem(zSTRING(meleeWeaponInstance.C_String()), 1);
						if( new_melee )
							npc->Equip(new_melee);
					}
				}
			}
			//Ranged
			if( npc->GetWeaponMode() != NPC_WEAPON_BOW && npc->GetWeaponMode() != NPC_WEAPON_CBOW )
			{
				oCItem* ranged = npc->GetEquippedRangedWeapon();
				if( ranged )
				{
					if( strcmp(rangedWeaponInstance.C_String(), "NULL") == 0 )
					{
						npc->UnequipItem(ranged);
					}
					else if( strcmp(rangedWeaponInstance.C_String(), ranged->GetInstanceName().ToChar()) != 0 )
					{
						npc->UnequipItem(ranged);
						oCItem* new_ranged = npc->CreateItem(zSTRING(rangedWeaponInstance.C_String()), 1);
						if( new_ranged )
						{
							npc->Equip(new_ranged);
						}
					}
				}
				else
				{
					if( strcmp( rangedWeaponInstance.C_String(), "NULL") != 0 )
					{
						oCItem* new_ranged = npc->CreateItem(zSTRING(rangedWeaponInstance.C_String()), 1);
						if( new_ranged )
							npc->Equip(new_ranged);
					}
				}
			}
		}
		timerWeapon = GetTimeMS() + 3000;
	}
};

void CPlayer::RefreshWeaponMode()
{
	if( npc->GetAttribute(NPC_ATR_HITPOINTS) > 0 && npc->IsUnconscious() == 0 )
	{
		if( weaponMode == 2 )
			weaponMode = 3;
		if (npc->GetWeaponMode() != weaponMode)
		{
			npc->SetWeaponMode((oCNpc_WeaponMode)weaponMode);
			// Repair hand item
			if (strcmp(leftHand.C_String(), "NULL") != 0 && !npc->GetLeftHand())
			{
				oCItem *item = npc->CreateItem(zSTRING(leftHand.C_String()), 1);
				if (item)
					npc->SetLeftHand(item);
			}
			if (strcmp(rightHand.C_String(), "NULL") != 0 && !npc->GetRightHand())
			{
				oCItem *item = npc->CreateItem(zSTRING(rightHand.C_String()), 1);
				if (item)
					npc->SetRightHand(item);
			}
		}
	}
};