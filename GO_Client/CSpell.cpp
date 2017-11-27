#include "stdafx.h"

void CSpell::StartSpellAction(oCNpc* npc, oCNpc* target, oCItem* magItem )
{
	if( npc && target && magItem )
	{
		const char* instanceName = magItem->GetInstanceName().ToChar();
		if( strcmp(instanceName, "ITARRUNESLEEP") == 0 )
		{
			if( !target->IsUnconscious() && !target->IsDead() )
			{
				if( strcmp(target->GetState().GetRoutineName().ToChar(), "ZS_MAGICSLEEP") != 0 )
					target->GetState().StartAIState(zSTRING("ZS_MAGICSLEEP"), false, 0, 0.0f, false); 
			}
		}
		else if( strcmp(instanceName, "ITARRUNEFIREBALL") == 0 || strcmp(instanceName, "ITARRUNEFIRESTORM") == 0 )
		{
			if( !target->IsUnconscious() && !target->IsDead() )
			{
				if( strcmp(target->GetState().GetRoutineName().ToChar(), "ZS_MAGICBURN") != 0 )
					target->GetState().StartAIState(zSTRING("ZS_MAGICBURN"), false, 0, 0.0f, false); 
			}
		}
		/*else if( strcmp(instanceName, "ITARRUNEICEWAVE") == 0 || strcmp(instanceName, "ITARRUNEICECUBE") == 0 )
		{
			if( !target->IsUnconscious() && !target->IsDead() )	
				target->GetState().StartAIState(zSTRING("ZS_MAGICFREEZE"), false, 0, 0.0f, false); 
		}*/
	}
}