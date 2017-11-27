#include "..\\..\\..\\stdafx.h"

void oCMag_Book::Hook_Spell_Cast()
{
	pMemLib->RemoveHook(0x0046FC00);
	if( this == oCNpc::GetHero()->GetSpellBook() )
	{
		DLOG("oCMag_Book::Hook_Spell_Cast()");
		if( core.GetNetwork()->IsInitiated() == true && core.GetNetwork()->IsConnected() == true )
			playerManager.GetLocalPlayer()->SendMagicAttack();
	}
	this->Spell_Cast();
	pMemLib->ImportHook(0x0046FC00, sizeof(void(oCMag_Book::*)(void)), &oCMag_Book::Hook_Spell_Cast);
};