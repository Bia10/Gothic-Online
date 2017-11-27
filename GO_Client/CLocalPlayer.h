#ifndef CLOCALPLAYER_H
#define CLOCALPLAYER_H

class CLocalPlayer : public CPlayer
{
private:
	//Timery
	unsigned int posBroadcastTimer;
	unsigned int angleBroadcastTimer;
	unsigned int weaponModeBroadcastTimer;
	unsigned int aniBroadcastTimer;
	unsigned int armorBroadcastTimer;
	unsigned int weaponBroadcastTimer;
	unsigned int instanceBroadcastTimer;
	unsigned int handBroadcastTimer;
	unsigned int standUpTimer;
	unsigned int fightBroadcastTimer;
	unsigned int worldBroadcastTimer;
	unsigned int protectionBroadcastTimer;
	unsigned int skillWeaponBroadcastTimer;
	unsigned int lastDeathTimer;
	unsigned int pingTimer;
	unsigned int focusTimer;
	bool isDead;
	
public:
	oCMobInter *lastMob;

	CLocalPlayer(int playerID, RakString playerName);
	~CLocalPlayer();

	void SetAdditionalVisuals(zSTRING &_bodyModel, int &_bodyTexture, zSTRING &_headModel, int &_headTexture);

	void Pulse();

	void SendPosition();
	void SendAngle();

	void SendChangeWeaponMode();
	//void SendPlayAnimation(int aniID, int startMode);
	void SendPlayAnimation();
	void SendWearArmor();
	void SendEquipWeapon(); //Ranged/Melee
	void SendInstanceChange(); //Zmiana w inna postac
	void SendHand(); //Poki co prawa reka (zablokowane bo kraszuje)
	void SendChangeLevel(RakString levelName);
	void SendEnterWorld();
	void SendHealth();
	void SendMaxHealth();
	void SendHitFocus(oCNpc *target);
	void SendStandUp();
	void SendMagicSetup();
	void SendMagicAttack();
	//void SendProtection();
	void SendMobTrigger(bool trigger, oCMobInter *mob);
	void SendOverlay(bool add, RakString overlay);
	void SendTimedOverlay(TimeMS time, RakString overlay);
	void SendArrow();
	void SendFocus(int playerID, int focusID, bool taken);
	void BroadcastWorld();
	void Respawn();
	void Unconscious();
	void ReleaseMob();
	void HandleFocus();
	void PingSelf();
	void BroadcastStats();
};

#endif //CLOCALPLAYER_H