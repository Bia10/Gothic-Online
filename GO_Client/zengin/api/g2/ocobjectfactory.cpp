#include "..\\..\\..\\stdafx.h"

oCItem* oCObjectFactory::CreateItem2(zSTRING& instance, zVEC3 pos, int amount)
{
	int index = zCParser::GetParser()->GetIndex(instance);
	if( index > 0 )
	{
		oCItem* item = CreateItem(index);
		if( item )
		{
			item->SetAmount(amount);
			oCNpc::GetHero()->DoDropVob(item); //Musimy wywalic w taki sposob ale nie laguje
			item->SetPositionWorld(pos);
			return item;
		}
	}
	return NULL;
};

zCVob* oCObjectFactory::CreateVob(zSTRING& visualName, int colldet, zVEC3 pos, zVEC3 rotation)
{
	zCVob* vob = (zCVob*)zCVob::_CreateNewInstance();
	if( vob )
	{
		vob -> SetCollDet(colldet);
		vob -> SetVisual(visualName);
		vob -> SetPositionWorld(pos);
		vob -> SetRotation(rotation);
		oCGame* game = oCGame::GetGame();
		if( game )
		{
			zCWorld* world = game->GetGameWorld();
			if( world )
			{
				world->AddVob(vob);
				return vob;
			}
		}
	}
	return NULL;
};

zCVob* oCObjectFactory::CreateMob(zSTRING &visualName, int colldet, zVEC3 pos, zVEC3 rotation, zTVobTypeVT mobType)
{
	zCVob* vob = NULL;
	switch(mobType)
	{
	case VOB_TYPE_VT_OCMOBBED:
		vob = (zCVob*)oCMobBed::_CreateNewInstance();
		break;
	case VOB_TYPE_VT_OCMOBCONTAINER:
		vob = (zCVob*)oCMobContainer::_CreateNewInstance();
		break;
	case VOB_TYPE_VT_OCMOBDOOR:
		vob = (zCVob*)oCMobDoor::_CreateNewInstance();
		break;
	case VOB_TYPE_VT_OCMOBFIRE:
		vob = (zCVob*)oCMobFire::_CreateNewInstance();
		break;
	case VOB_TYPE_VT_OCMOBINTER:
		vob = (zCVob*)oCMobInter::_CreateNewInstance();
		break;
	case VOB_TYPE_VT_OCMOBITEMSLOT:
		vob = (zCVob*)oCMobItemSlot::_CreateNewInstance();
		break;
	case VOB_TYPE_VT_OCMOBLADDER:
		vob = (zCVob*)oCMobLadder::_CreateNewInstance();
		break;
	case VOB_TYPE_VT_OCMOBMSG:
		vob = (zCVob*)oCMobMsg::_CreateNewInstance();
		break;
	case VOB_TYPE_VT_OCMOBSWITCH:
		vob = (zCVob*)oCMobSwitch::_CreateNewInstance();
		break;
	case VOB_TYPE_VT_OCMOBWHEEL:
		vob = (zCVob*)oCMobSwitch::_CreateNewInstance();
		break;
	default:
		return CreateVob(visualName,colldet,pos,rotation);
	};
	if( vob )
	{
		vob->SetCollDet(colldet);
		vob->SetVisual(visualName);
		vob->SetPositionWorld(pos);
		vob->SetRotation(rotation);
		zCWorld* world = oCGame::GetGame()->GetGameWorld();
		if( world )
		{
			world->AddVob(vob);
			return vob;
		}
	}
	return NULL;
};