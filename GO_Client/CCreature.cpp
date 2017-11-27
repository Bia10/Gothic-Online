#include "stdafx.h"

CCreature::CCreature()
{
	DLOG("CCreature::CCreature()");
	id = -1;
	npc = NULL;
	instance = "PC_HERO";
	world = "WORLD.zen";
	maxhealth = 40;
	health = 40;
	maxmana = 40;
	mana = 40;
	animationId = 0;

	protection[0] = 0; protection[1] = 0;
	protection[2] = 0; protection[3] = 0;

	skillWeapon[0] = 0; skillWeapon[1] = 0;

	armorInstance = "NULL";
	meleeWeaponInstance = "NULL";
	rangedWeaponInstance = "NULL";
	rightHand = "NULL";
	leftHand = "NULL";

	bodyModel = "hum_body_Naked0";
	headModel = "Hum_Head_Pony";
	bodyTexture = 4;
	headTexture = 9;

	spellItem = NULL;
	weaponMode = 0;
	unconscious = false;
	dead = false;
	spellID = -1;
	angle = 0.0f;

	pos.Set(0.0f, 200.0f, 0.0f);
};

CCreature::~CCreature()
{
	DLOG("CCreature::~CCreature() ID = %d", this->id);
	instance.FreeMemory();
	world.FreeMemory();
	armorInstance.FreeMemory();
	meleeWeaponInstance.FreeMemory();
	rangedWeaponInstance.FreeMemory();
	rightHand.FreeMemory();
	leftHand.FreeMemory();
};

void CCreature::GetAdditionalVisuals(zSTRING &_bodyModel, int &_bodyTexture, zSTRING &_headModel, int &_headTexture)
{
	_bodyModel = bodyModel;
	_headModel = headModel;
	_bodyTexture = bodyTexture;
	_headTexture = headTexture;
}