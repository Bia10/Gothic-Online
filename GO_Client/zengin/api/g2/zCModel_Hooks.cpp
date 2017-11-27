#include "..\\..\\..\\stdafx.h"

void zCModel::Hook_StartAni(zCModelAni *pA, int pB)
{
	pMemLib->RemoveHook(0x005612F0);
	if (!CAnimation::GetInstance().IsAniBlockedForAll(pA))
	{
		//core.GetChat()->AddLine(RakString("%s %d %d", pA->GetAniName().ToChar(), pA->GetAniID(), pB), zCOLOR(255, 255, 0));
		//this->StartAni(pA, pB);
		if(oCNpc::GetHero())
		{
			if (this == oCNpc::GetHero()->GetModel())
			{
				if (pA)
				{
					if (CAnimation::GetInstance().IsAnimationTurning(pA->GetAniName().ToChar()) == false && pA->GetAniID() > 0)
					{
						core.GetChat()->AddLine(RakString("AniName: %s ID:%d", pA->GetAniName().ToChar(), pA->GetAniID()), zCOLOR(255, 0, 0, 255));
						this->StartAni(pA, pB);
						/*int aniID = pA->GetAniID();
						if (core.GetNetwork()->IsConnected() == true)
						{
							//playerManager.GetLocalPlayer()->SendPlayAnimation(aniID, pB);
						}*/
					}
				}
			}
			else
				this->StartAni(pA, pB);
		}
	}
	pMemLib->ImportHook(0x005612F0, sizeof(void(zCModel::*)(zCModelAni*,int)), &zCModel::Hook_StartAni);
};