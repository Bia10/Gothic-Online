#include "stdafx.h"

CVobManager::CVobManager()
{
	vobList.Clear();
};

CVobManager::~CVobManager()
{
	vobList.DeleteContentsAndClear();
};

size_t CVobManager::GetFreeID()
{
	if( GetNumberOfVobs() > 0 )
	{
		for( unsigned int i = 0; ; ++i )
		{
			for( unsigned int j = 0; ; ++j )
			{
				if( i == vobList[j]->GetID() )
					break;
				else if( j == GetNumberOfVobs() - 1 && i != vobList[j]->GetID() )
				{
					return i;
				}
			}
		}
	}
	else
		return 0;
};

CVob* CVobManager::CreateVob(zSTRING &visual, zVEC3 position, zVEC3 rot)
{
	CVob* vob = new CVob(visual,position,rot,GetFreeID());
	if( vob )
	{
		vobList.PushBack(vob);
		return vob;
	}
	return NULL;
};

bool CVobManager::DestroyVob(CVob *vob)
{
	if( vob )
	{
		if( vobList.Remove(vob) == true )
		{
			delete vob;
			return true;
		}
	}
	return false;
};

CVob* CVobManager::GetById(int ID)
{
	for( size_t i = 0; i < GetNumberOfVobs(); ++i )
		if( vobList[i]->GetID() == ID )
			return vobList[i];
	return NULL;
};

CVob* CVobManager::GetByPosition(zVEC3 position)
{
	for( size_t i = 0; i < GetNumberOfVobs(); ++i )
	{
		zVEC3 pos = vobList[i]->GetZVob()->GetPositionWorld();
		if( goMath::GetDistance3D(position.x, position.y, position.z, pos.x, pos.y, pos.z) <= 10 )
			return vobList[i];
	}
	return NULL;
};