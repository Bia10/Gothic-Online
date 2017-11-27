#include "stdafx.h"

CCreature::CCreature()
{
	//DLOG("CCreature::CCreature()\n");

	id                  = -1;
	isNpc               = false;
	spawned             = false;
	isDead				= false;
	isUnconscious		= false;
	maxhealth           = 40;
	health              = 40;

	protection[0] = 0; protection[1] = 0;
	protection[2] = 0; protection[3] = 0;

	skillWeapon[0] = 0; skillWeapon[1] = 0;

	instance            = "PC_HERO";
	world				= "NEWWORLD\\NEWWORLD.ZEN";
	x                   = 0.0f;
	y                   = 200.0f;
	z                   = 0.0f;
	angle				= 0.0f;

	bodyModel = "Hum_Body_Naked0";
	headModel = "Hum_Head_Pony";
	bodyTexture = 9;
	headTexture = 18;

	overlay = "NONE";

	weaponMode			= 0;
	animationId			= 0;
	armorInstance	= "NULL";
	meleeWeaponInstance = "NULL";
	rangedWeaponInstance = "NULL";
	leftHand = "NULL";
	rightHand = "NULL";
	magicItem = "NULL";
	isInvisible = false;
	isAdmin = false;
	virtualWorld = 0;
};

CCreature::~CCreature()
{
	//DLOG("CCreature::~CCreature()\n");
	instance.FreeMemory();
	world.FreeMemory();
	armorInstance.FreeMemory();
	meleeWeaponInstance.FreeMemory();
	rangedWeaponInstance.FreeMemory();
	leftHand.FreeMemory();
	rightHand.FreeMemory();
	magicItem.FreeMemory();
};