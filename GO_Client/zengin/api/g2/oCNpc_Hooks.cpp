#include "..\\..\\..\\stdafx.h"

int oCNpc::Hook_DoDropVob(zCVob *vob)
{
	pMemLib->RemoveHook(0x006A10F0);
	oCItem* item = reinterpret_cast<oCItem*>(vob);
	if( strcmp(item->GetInstanceName().ToChar(), "ITLSTORCHBURNING") != 0 )	//Jebane pochodnie
	{
		if( this == oCNpc::GetHero() )
		{
			this->_DoDropVob(vob);
			itemManager.SendDropItem(RakString(item->GetInstanceName().ToChar()), item->GetPositionWorld(), item->GetAmount());
			vob->RemoveVobFromWorld();
		}
		else
			this->_DoDropVob(vob);
	}
	pMemLib->ImportHook(0x006A10F0, sizeof(int(oCNpc::*)(zCVob*)), &oCNpc::Hook_DoDropVob);
	return 0;
};               

int oCNpc::Hook_DoTakeVob(zCVob *vob)
{
	pMemLib->RemoveHook(0x006A0D10);
	//core.GetChat()->AddLine(RakString("Take item"), zCOLOR(255,0,0,255));
	if( this == oCNpc::GetHero() )
	{
		this->_DoTakeVob(vob);
		/*if( itemManager.SendTakeItem(reinterpret_cast<oCItem*>(vob)) == false )
			this->DoDropVob(vob);*/
		itemManager.SendTakeItem(reinterpret_cast<oCItem*>(vob));
	}
	else
		this->_DoTakeVob(vob);
	pMemLib->ImportHook(0x006A0D10, sizeof(int(oCNpc::*)(zCVob*)), &oCNpc::Hook_DoTakeVob);
	//Wysy³anie podniesienia itemu
	return 0;
};

void oCNpc::Hook_SetMovLock(int e)
{
	pMemLib->RemoveHook(0x00694C50);
	SetMovLock(scr.GetScriptVars()->isFrozen ? true : e);
	pMemLib->ImportHook(0x00694C50, sizeof(void(oCNpc::*)(int)), &oCNpc::Hook_SetMovLock);
};

void oCNpc::Hook_OpenInventory()
{
	pMemLib->RemoveHook(0x006BB0A0);

	if (scr.GetScriptVars()->isEqEnabled && !scr.GetScriptVars()->isFrozen)
	{
		OpenInventory();
		if (IsInvOpen()) SCallback::onOpenInventory();
	}
		
	pMemLib->ImportHook(0x006BB0A0, sizeof(void(oCNpc::*)(void)), &oCNpc::Hook_OpenInventory);
};

void oCNpc::Hook_CloseInventory()
{
	pMemLib->RemoveHook(0x006BB2F0);

	if (IsInvOpen())
	{
		CloseInventory();
		SCallback::onCloseInventory();
	}

	pMemLib->ImportHook(0x006BB2F0, sizeof(void(oCNpc::*)(void)), &oCNpc::Hook_CloseInventory);
}; 

int oCNpc::Hook_ApplyOverlay(zSTRING &overlay)
{
	pMemLib->RemoveHook(0x0068AD40);

	int result = ApplyOverlay(overlay);
	if (this == oCNpc::GetHero() && result)
		playerManager.GetLocalPlayer()->SendOverlay(true, overlay.ToChar());

	pMemLib->ImportHook(0x0068AD40, sizeof(int(oCNpc::*)(zSTRING&)), &oCNpc::Hook_ApplyOverlay);
	return result;
};

void oCNpc::Hook_RemoveOverlay(zSTRING &overlay)
{
	pMemLib->RemoveHook(0x0068B040);
	RemoveOverlay(overlay);
	if (this == oCNpc::GetHero())
		playerManager.GetLocalPlayer()->SendOverlay(false, overlay.ToChar());
	pMemLib->ImportHook(0x0068B040, sizeof(void(oCNpc::*)(zSTRING&)), &oCNpc::Hook_RemoveOverlay);
};

int oCNpc::Hook_ApplyTimedOverlayMds(zSTRING &overlay, float time)
{
	pMemLib->RemoveHook(0x006B0C60);

	int result = ApplyTimedOverlayMds(overlay, time);
	if (this == oCNpc::GetHero() && result)
		playerManager.GetLocalPlayer()->SendTimedOverlay(time, overlay.ToChar());

	pMemLib->ImportHook(0x006B0C60, sizeof(int(oCNpc::*)(zSTRING&, float)), &oCNpc::Hook_ApplyTimedOverlayMds);
	return result;
}

void oCNpc::Hook_DropUnconscious(float time, oCNpc* npc)
{
	pMemLib->RemoveHook(0x00692C10);
	if (scr.GetScriptVars()->isUnconsciousEnabled)
		this->DropUnconscious(time, npc);
	pMemLib->ImportHook(0x00692C10, sizeof(void(oCNpc::*)(float, oCNpc*)), &oCNpc::Hook_DropUnconscious);
}

void oCNpc::Hook_DoShootArrow(int p)
{
	pMemLib->RemoveHook(0x006A09F0);
	if (this == oCNpc::GetHero())
		playerManager.GetLocalPlayer()->SendArrow();
	this->DoShootArrow(p);
	pMemLib->ImportHook(0x006A09F0, sizeof(void(oCNpc::*)(int)), &oCNpc::Hook_DoShootArrow);
}

void oCNpc::Hook_OnDamage_Anim(oSDamageDescriptor &dmgDes)
{
	//pMemLib->RemoveHook(0x00741990);
	//pMemLib->ImportHook(0x00741990, sizeof(void(oCNpc::*)(oSDamageDescriptor&)), &oCNpc::Hook_OnDamage);
}

void oCNpc::Hook_OnDamage_Script(oSDamageDescriptor &dmgDes) //0x00738E40
{
	pMemLib->RemoveHook(0x00738E40);
	if (scr.GetScriptVars()->isSpawningEnabled)
		this->OnDamage_Script(dmgDes);

	if (this != oCNpc::GetHero() && dmgDes.pNpcAttacker == oCNpc::GetHero())
		playerManager.GetLocalPlayer()->SendHitFocus(this);
	pMemLib->ImportHook(0x00738E40, sizeof(void(oCNpc::*)(oSDamageDescriptor&)), &oCNpc::Hook_OnDamage_Script);
}

void oCNpc::Fake_DropAllInHand()
{
	return;
};


void oCNpc::Fake_Disable()
{
	/*if( playerManager.IsPlayerSynchronised(this) == true )
		return;
	else
	{
		pMemLib->RemoveHook(0x006A1D20);
		this->Disable();
		pMemLib->ImportHook(0x006A1D20, sizeof(void(oCNpc::*)()), &oCNpc::Fake_Disable);
	}*/
	return;
};