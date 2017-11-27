#include "..\\..\\..\\stdafx.h"

bool MobType::IsDoor(zSTRING& visual)
{
	const char* vis = visual.Upper().ToChar();
	for(size_t i = 0; i < 5; ++i)
		if(strcmp(mobDoor[i], vis) == 0)
			return true;
	return false;
};

bool MobType::IsBed(zSTRING& visual)
{
	const char* vis = visual.Upper().ToChar();
	for(size_t i = 0; i < 13; ++i)
		if(strcmp(mobBed[i], vis) == 0)
			return true;
	return false;
};

bool MobType::IsLadder(zSTRING& visual)
{
	const char* vis = visual.Upper().ToChar();
	for(size_t i = 0; i < 9; ++i)
		if(strcmp(mobLadder[i], vis) == 0)
			return true;
	return false;
};

bool MobType::IsInter(zSTRING& visual)
{
	const char* vis = visual.Upper().ToChar();
	for(size_t i = 0; i < 44; ++i)
		if(strcmp(mobInter[i], vis) == 0)
			return true;
	return false;
};

void oCMobInter::Hook_OnTrigger(zCVob *target, zCVob *sender)
{
	pMemLib->RemoveHook(0x0067D300);
	if (this->GetS1() && !this->GetS2())
	{
		if (oCNpc::GetHero() == (oCNpc*)sender)
		{
			int result = SCallback::onMobTrigger(this);

			switch (::GetVobType(this))
			{
			case VOB_TYPE_VT_OCMOBSWITCH:
			case VOB_TYPE_VT_OCMOBWHEEL:
			case VOB_TYPE_VT_OCMOBDOOR:
				playerManager.GetLocalPlayer()->SendMobTrigger(true, this);
				break;
			case VOB_TYPE_VT_OCMOBINTER:
			case VOB_TYPE_VT_OCMOBCONTAINER:
				if (!this->GetName().IsEmpty() || result)
				{
					playerManager.GetLocalPlayer()->lastMob = this;
					playerManager.GetLocalPlayer()->SendMobTrigger(true, this);
				}
				break;
			}
		}
		this->OnTrigger(target, sender);
	}
	pMemLib->ImportHook(0x0067D300, sizeof(void(oCMobInter::*)(zCVob*, zCVob*)), &oCMobInter::Hook_OnTrigger);
}

void oCMobInter::Hook_OnUntrigger(zCVob *target, zCVob *sender)
{
	pMemLib->RemoveHook(0x0067D5F0);
	if (!this->GetS1() && this->GetS2())
	{
		if (oCNpc::GetHero() == (oCNpc*)sender)
		{
			int result = SCallback::onMobUntrigger(this);

			switch (::GetVobType(this))
			{
			case VOB_TYPE_VT_OCMOBSWITCH:
			case VOB_TYPE_VT_OCMOBWHEEL:
			case VOB_TYPE_VT_OCMOBDOOR:
				playerManager.GetLocalPlayer()->SendMobTrigger(false, this);
				break;
			case VOB_TYPE_VT_OCMOBINTER:
			case VOB_TYPE_VT_OCMOBCONTAINER:
				if (!this->GetName().IsEmpty() || result)
				{
					playerManager.GetLocalPlayer()->lastMob = NULL;
					playerManager.GetLocalPlayer()->SendMobTrigger(false, this);
				}
				break;
			}
		}
		this->OnUntrigger(target, sender);
	}
	pMemLib->ImportHook(0x0067D5F0, sizeof(void(oCMobInter::*)(zCVob*, zCVob*)), &oCMobInter::Hook_OnUntrigger);
}