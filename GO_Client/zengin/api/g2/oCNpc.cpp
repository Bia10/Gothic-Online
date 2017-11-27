#include "..\\..\\..\\stdafx.h"



zCModelAni* oCNpc::GetCurrentAni()
{
	zCModel* model = GetModel();
	if( model )
	{
		for( size_t i = 1; i < 1210; i++ )
		{
			zCModelAni* animation = model->GetAniFromAniID(i);
			if( animation )
			{
				if( CAnimation::GetInstance().IsAniBlockedForAll(animation) == false && CAnimation::GetInstance().IsAnimationTurning(RakString(animation->GetAniName().ToChar())) == false )
				{
					if( model->IsAnimationActive(animation->GetAniName()) )
					{
						if( !IsHuman() )
						{
							if( i != 341 )
								return animation;
						}
						else return animation;		
					}
				}
			}
		}
	}
	return NULL;
};

zSTRING oCNpc::GetAnimationName()
{
	zCModelAni *model = GetCurrentAni();
	if (model)
		return model->GetAniName();

	return zSTRING("UNKNOWN");
}

int oCNpc::GetAnimationID()
{
	zCModelAni *model = GetCurrentAni();
	if (model)
		return model->GetAniID();

	return -1;
}

void oCNpc::SetSkillWeapon(int skillID, unsigned value)
{
	if (skillID > 0 && skillID <= 4)
	{
		if (value >= 0 && value < 30)
			SetTalentSkill(skillID, LOW);
		else if (value >= 30 && value < 60)
			SetTalentSkill(skillID, MEDIUM);
		else if (value >= 60 && value <= 100)
			SetTalentSkill(skillID, MASTER);

		SetTalentValue(skillID, value);
	}
};

int oCNpc::GetSkillWeapon(int skillID)
{
	if (skillID > 0 && skillID <= 4)
		return GetTalentValue(skillID);

	return 0;
};

void oCNpc::SetProtection(int type, int value)
{
	if (value < 0) value = 0;

	switch (type)
	{
	case PROT_WEAPON:
		*(int*)((DWORD)this + 0x1A8) = value;
		*(int*)((DWORD)this + 0x1A4) = value;
		break;

	case PROT_ARROW:
		*(int*)((DWORD)this + 0x1BC) = value;
		break;

	case PROT_FIRE:
		*(int*)((DWORD)this + 0x1B0) = value;
		break;

	case PROT_MAGIC:
		*(int*)((DWORD)this + 0x1B8) = value;
		break;
	}
};

int oCNpc::GetProtection(int type)
{
	switch (type)
	{
	case PROT_WEAPON:
		return *(int*)((DWORD)this + 0x1A4);
		break;

	case PROT_ARROW:
		return *(int*)((DWORD)this + 0x1BC);
		break;

	case PROT_FIRE:
		return *(int*)((DWORD)this + 0x1B0);
		break;

	case PROT_MAGIC:
		return *(int*)((DWORD)this + 0x1B8);
		break;
	}

	return 0;
};

int oCNpc::DoDropVob(zCVob* vob)	//0x006A10F0
{
	pMemLib->RemoveHook(0x006A10F0);
	this->_DoDropVob(vob);
	pMemLib->ImportHook(0x006A10F0, sizeof(int(oCNpc::*)(zCVob*)), &oCNpc::Hook_DoDropVob);
	return 0;
};

int oCNpc::DoTakeVob(zCVob* vob)	//0x006A0D10
{
	pMemLib->RemoveHook(0x006A0D10);
	this->_DoTakeVob(vob);
	pMemLib->ImportHook(0x006A0D10, sizeof(int(oCNpc::*)(zCVob*)), &oCNpc::Hook_DoTakeVob);
	return 0;
};

void oCNpc::ClearInventory()
{
	oCItem* melee = GetEquippedMeleeWeapon();
	oCItem* ranged = GetEquippedRangedWeapon();
	oCItem* armor = GetEquippedArmor();
	if( melee )
	{
		UnequipItem(melee);
		DoDropVob(melee);
		melee->RemoveVobFromWorld();
	}
	if( ranged )
	{
		UnequipItem(ranged);
		DoDropVob(ranged);
		ranged->RemoveVobFromWorld();

	}
	if( armor )
	{
		UnequipItem(armor);
		DoDropVob(armor);
		armor->RemoveVobFromWorld();
	}
	oCItem* item = NULL;
	for( int i = 0; i < 2; ++i )	//Trzeba usuwaæ dwa razy bo nie wywala wszystkich itemów za pierwszym
	{
		for( int j = 0; j < 5000; ++j )
		{
			item = IsInInv(j,0);
			if( item )
			{
				DoDropVob(item);
				item->RemoveVobFromWorld();
			}
			item = NULL;
		}
	}
};

void oCNpc::ForceStandUp()
{
	this->DoDie();
	this->SetAttribute(NPC_ATR_HITPOINTS, 1);

	zCModel* model = this->GetModel();
	if( model )
	{
		if(model->IsAnimationActive(zSTRING("S_WOUNDEDB")))
			model->StartAni(zSTRING("T_WOUNDEDB_2_STAND"),0);
		else if(model->IsAnimationActive(zSTRING("S_WOUNDED")))
			model->StartAni(zSTRING("T_WOUNDED_2_STAND"),0);
	}

};

oCItem* oCNpc::CreateItem(zSTRING& instance, int amount) //Przetestowac ta funkcje przy SetLeftHand
{
	int insIndex = zCParser::GetParser()->GetIndex(instance);
	if( insIndex > 0 )
	{
		oCItem* item = oCObjectFactory::GetFactory()->CreateItem(insIndex);
		if(item)
		{
			item->SetAmount(amount);
			this->DoPutInInventory(item);
			return item;
		}

	}
	return NULL;
};

void oCNpc::DestroyNpc()
{
	oCGame* game = oCGame::GetGame();
	if( game )
	{
		zCWorld* world = game->GetGameWorld();
		if( world )
		{
			if( this )
			{
				world->RemoveVob(this);
			}
		}

	}
};

oCItem* oCNpc::PutInInv(const zSTRING& instance, int amount)
{
	int insIndex = zCParser::GetParser()->GetIndex(instance);

	if(insIndex > 0) //Standardowa gothicowa funkcja wywoluje crasha
	{
		return this->PutInInv(insIndex, amount);
	}
	return NULL;
};

void oCNpc::SetHeading(float angle)
{
	this->ResetRotationsWorld();
	this->RotateWorldY(angle);
};

float oCNpc::GetHeading()
{
	float x = *(float*)((DWORD)this + 0x44); //Glownie operujemy na tym
	float rotx = asin(x) * 180.0f / 3.14f;

	float y = *(float*)((DWORD)this + 0x64); // +/- (+ polnocna, - poludniowa)

	if(y > 0) //Polnocna polkula
	{
		if(x < 0)
			rotx = 360 + rotx;
	}
	else //Poludniowa polkula
	{
		if(rotx > 0) // (90 < rotx < 180)
			rotx = 180 - rotx;
		else //(x < 0) | (180 < rotx < 270)
		{
			rotx = 180 + rotx;
				rotx = 360 - rotx;
		}
	}										
	return rotx;
};

void oCNpc::_SetMovLock(int e)
{
	pMemLib->RemoveHook(0x00694C50);
	SetMovLock(e);
	pMemLib->ImportHook(0x00694C50, sizeof(void(oCNpc::*)(int)), &oCNpc::Hook_SetMovLock);
};

void oCNpc::_OpenInventory()
{
	pMemLib->RemoveHook(0x006BB0A0);
	OpenInventory();
	pMemLib->ImportHook(0x006BB0A0, sizeof(void(oCNpc::*)(void)), &oCNpc::Hook_OpenInventory);
};

void oCNpc::_CloseInventory()
{
	pMemLib->RemoveHook(0x006BB2F0);
	CloseInventory();
	pMemLib->ImportHook(0x006BB2F0, sizeof(void(oCNpc::*)(void)), &oCNpc::Hook_CloseInventory);
};

int oCNpc::_ApplyOverlay(zSTRING &overlay)
{
	pMemLib->RemoveHook(0x0068AD40);
	int returned = ApplyOverlay(overlay);
	pMemLib->ImportHook(0x0068AD40, sizeof(int(oCNpc::*)(zSTRING&)), &oCNpc::Hook_ApplyOverlay);

	return returned;
};

void oCNpc::_RemoveOverlay(zSTRING &overlay)
{
	pMemLib->RemoveHook(0x0068B040);
	RemoveOverlay(overlay);
	pMemLib->ImportHook(0x0068B040, sizeof(void(oCNpc::*)(zSTRING&)), &oCNpc::Hook_RemoveOverlay);
};

void oCNpc::SetAsPlayer()
{
	this->_SetAsPlayer();
	*(oCNpc**)0x0086A3DC = this;
};