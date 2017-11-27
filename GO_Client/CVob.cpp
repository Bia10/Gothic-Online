#include "stdafx.h"

CVob::CVob(zSTRING& visual, zVEC3 position, zVEC3 rot, int ID) : rotation(rot), id(ID)
{
	if( MobType::IsBed(visual) == true )
		zVob = oCObjectFactory::GetFactory()->CreateMob(visual,0,position,rot,VOB_TYPE_VT_OCMOBBED);
	else if( MobType::IsDoor(visual) == true )
		zVob = oCObjectFactory::GetFactory()->CreateMob(visual,0,position,rot,VOB_TYPE_VT_OCMOBDOOR);
	else if( MobType::IsLadder(visual) == true )
		zVob = oCObjectFactory::GetFactory()->CreateMob(visual,0,position,rot,VOB_TYPE_VT_OCMOBLADDER);
	else if( MobType::IsInter(visual) == true )
		zVob = oCObjectFactory::GetFactory()->CreateMob(visual,0,position,rot,VOB_TYPE_VT_OCMOBINTER);
	else
		zVob = oCObjectFactory::GetFactory()->CreateVob(visual,0, position, rot);
};	

CVob::CVob(zCVob *vob, int ID) : zVob(vob), id(ID)
{
};

CVob::~CVob()
{
	if( zVob )
		zVob->RemoveVobFromWorld();
};

void CVob::SetRotation(zVEC3 rot)
{
	rotation = rot;
	if( zVob )
		zVob->SetRotation(rot.x, rot.y, rot.z);
};