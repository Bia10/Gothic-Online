#ifndef CCREATURE_H
#define CCREATURE_H

class CCreature
{
public:
	int id;
	RakString name;

	RakString instance;
	bool spawned;
	bool isDead;
	bool isUnconscious;
	RakString world;
	float x;
	float y;
	float z;
	float angle;
	int maxhealth;
	int health;
	int maxmana;
	int mana;
	int protection[4];
	int skillWeapon[2];
	
	int animationId;

	RakString armorInstance;
	RakString meleeWeaponInstance;
	RakString rangedWeaponInstance;
	RakString leftHand;
	RakString rightHand;
	RakString magicItem;

	RakString bodyModel, headModel;
	int bodyTexture, headTexture;

	RakString overlay;

	int weaponMode;

	bool isNpc;
	bool isAdmin;
	bool isInvisible;

	unsigned virtualWorld;

	CCreature();
	~CCreature();

};

#endif //CCREATURE_H