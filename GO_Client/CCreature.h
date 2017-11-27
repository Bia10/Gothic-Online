#ifndef CCREATURE_H
#define CCREATURE_H

class CCreature
{
public:
	int id;
	RakString name;

	RakString instance;
	oCNpc* npc;
	RakString world;
	zVEC3 pos;
	float angle;
	int maxhealth;
	int health;
	int maxmana;
	int mana;
	int spellID;
	int protection[4];
	int skillWeapon[2];

	bool unconscious;
	bool dead;

	RakString leftHand;
	RakString rightHand;
	RakString armorInstance;
	RakString meleeWeaponInstance;
	RakString rangedWeaponInstance;

	zSTRING bodyModel, headModel;
	int bodyTexture, headTexture;

	oCItem* spellItem;

	int weaponMode;

	int animationId;

	bool isNpc;

	CCreature();
	~CCreature();

	inline int GetID() const{ return this->id;};
	inline RakString& GetName(){ return this->name; };
	void GetAdditionalVisuals(zSTRING &_bodyModel, int &_bodyTexture, zSTRING &_headModel, int &_headTexture);
};

#endif //CCREATURE_H