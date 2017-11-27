#include "..\\..\\..\\stdafx.h"


oCNpc* oCGame::CreateNPC(zSTRING& instance, float x, float y, float z)
{
	int insIndex = zCParser::GetParser()->GetIndex(instance);
	if(insIndex > 0)
	{
		oCNpc* npc = oCObjectFactory::GetFactory()->CreateNpc(insIndex);
		if( npc )
		{
			npc->Enable(zVEC3(x, y, z));
			npc->SetPositionWorld(zVEC3(x,y,z));
			npc->SetAttitude(NPC_ATTITUDE_FRIENDLY); //¯eby nie atakowa³ bez powodu
			if( npc->IsHuman() )
			{
				npc->SetFlag(1);
				npc->ClearInventory();
			}
		return npc;
		}
	}
	DLOG("Cannot create npc");
	return NULL;
};