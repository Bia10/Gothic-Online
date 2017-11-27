#ifndef CPLAYER_H
#define CPLAYER_H

class CPlayer : public CCreature
{
public:
	CPlayer();
	CPlayer(int playerID, RakString playerName);
	~CPlayer();

	void Spawn(float x, float y, float z, RakString instance);
	void Respawn(); //Naprawienie buga ze smiercia
	void UnSpawn();
	void SetAdditionalVisuals(zSTRING &_bodyModel, int &_bodyTexture, zSTRING &_headModel, int &_headTexture);
private:
	size_t timerSlide;
	bool isSlideAllowed;
	size_t timerArmor;
	size_t timerWeapon;
	size_t timerHealth;
public:
	void Repair();
private:
	void RefreshPositions();
	void RefreshAngle();
	void RefreshArmor();
	void RefreshWeapon();
	void RefreshWeaponMode();
	void RefreshHealth();
	void RefreshTemporaryAnimation();
};

#endif //CPLAYER_H