#include "stdafx.h"

CAnimation::CAnimation()
{
	DLOG("CAnimation::CAnimation()");
};

CAnimation::~CAnimation()
{
	DLOG("CAnimation::~CAnimation()");
};

bool CAnimation::IsAnimationTurning(RakString aniName)
{
	for( unsigned int i = 0; i < 44; i++ )
	{
		if( strcmp(AnimationTurning[i], aniName.C_String()) == 0 )
			return true;
	}
	return false;
};

int CAnimation::GetAnimationMove(oCNpc *npc)
{
	if( npc )
	{
		zCModel* model = npc->GetModel();

		if( model )
		{
			for( unsigned int i = 0; i < 22; i++ )
			{
				if( model->IsAnimationActive(zSTRING(AnimationMove[i])) )
					return model->GetAniIDFromAniName(zSTRING(AnimationMove[i]));
			}
		}
	}
	return 0;
};

bool CAnimation::IsAnimationMoveActive(oCNpc* npc)
{
	if( npc )
	{
		zCModel* model = npc->GetModel();

		if( model )
		{
			for( unsigned int i = 0; i < 22; i++ )
			{
				if( model->IsAnimationActive(zSTRING(AnimationMove[i])) )
					return true;
			}
		}
	}
	return false;
};

int CAnimation::GetAnimationHandAction(oCNpc* npc)
{
	if( npc )
	{
		zCModel* model = npc->GetModel();
		if( model )
		{
			for( unsigned int i = 0; i < 21; i++ )
			{
				if( model->IsAnimationActive(zSTRING(AnimationHandAction[i])) )
					return model->GetAniIDFromAniName(zSTRING(AnimationHandAction[i]));
			}
		}
	}
	return 0;
};

bool CAnimation::IsAnimationHandActionActive(oCNpc *npc)
{
	if( npc )
	{
		zCModel* model = npc->GetModel();
		if( model )
		{
			for( unsigned int i = 0; i < 21; i++ )
			{
				if( model->IsAnimationActive(zSTRING(AnimationHandAction[i])) )
					return true;
			}
		}
	}

	return false;
};

bool CAnimation::IsAniBlockedForAll(zCModelAni* modelAni)
{
	if( modelAni )
	{
		for( unsigned int i = 0; i < 8; i++ )
		{
			if( strcmp(modelAni->GetAniName().ToChar(), BlockedAnimationsForAll[i]) == 0 )
				return true;
		}
	}
	return false;
};