/* Gothic Online ZenGin research (based on g2ext) */


#ifndef __API_G2_OCNPC_H__
#define __API_G2_OCNPC_H__

#ifndef __G2EXT_API_HEADER
#define __G2EXT_API_HEADER
#endif  //__G2EXT_API_HEADER

#ifdef _G2EXT_COMPILE_SPACER
#error Cannot use gothic headers on spacer dll (_G2EXT_COMPILE_SPACER defined)
#endif

#include "api/g2/ztypes.h"
#include "api/g2/zstring.h"

#include "api/g2/zcobject.h"
#include "api/g2/ocvob.h"
#include "api/g2/ocitem.h"
#include "api/g2/ocnpcinventory.h"
#include "api/g2/ocmob.h"
#include "api/g2/ocanictrl_human.h"

class oCAskBox;
class oCInfo;
class oCMission;
class oCNews;
class oCNpc;
class oCNpcMessage;
class oCNpcTalent;
class oCNpcTimedOverlay;
class oCRtnEntry;
class oCSpell;
class oCVisualFX;
class TNpcSlot;
class zCPlayerGroup;
class zCRoute;
class zCParticleFX;
class zTSoundHandle;
class oTDirectionInfo;
class zCModel;
class zCModelAni;

enum oCNpc_Attribute
{
	NPC_ATR_HITPOINTS, 
	NPC_ATR_HITPOINTS_MAX,
	NPC_ATR_MANA,
	NPC_ATR_MANA_MAX,
	NPC_ATR_STRENGTH,
	NPC_ATR_DEXTERITY,
	NPC_ATR_REGENERATEHP,
	NPC_ATR_REGENERATEMANA,
	NPC_ATR_MAX
};

enum oCNpc_Hitchance
{
	NPC_HITCHANCE_1H,
	NPC_HITCHANCE_2H,
	NPC_HITCHANCE_BOW,
	NPC_HITCHANCE_CROSSBOW,
	NPC_HITCHANCE_MAX
};

enum oCNpc_Attitude
{ 
	NPC_ATTITUDE_HOSTILE, 
	NPC_ATTITUDE_ANGRY, 
	NPC_ATTITUDE_NEUTRAL, 
	NPC_ATTITUDE_FRIENDLY
};

enum oCNpc_Skill
{
	LOW,
	MEDIUM,
	MASTER
};

enum oCNpc_WeaponMode
{
	NPC_WEAPON_NONE = 0,
	NPC_WEAPON_FIST = 1,
	NPC_WEAPON_DAG  = 2,
	NPC_WEAPON_1HS	= 3,
	NPC_WEAPON_2HS  = 4, 
	NPC_WEAPON_BOW	= 5,
	NPC_WEAPON_CBOW = 6,
	NPC_WEAPON_MAG	= 7,
	NPC_WEAPON_MAX  = 8
};

enum oCNpc_Protection
{
	PROT_WEAPON,
	PROT_ARROW,
	PROT_FIRE,
	PROT_MAGIC
};

/** Insert description */
class oCMag_Book
{
private:
	char _data[64];
public:
	void Hook_Spell_Cast(void);
	void Spell_Setup(int snr, oCNpc* npc, zCVob* vob){XCALL(0x0046F6C0);};
	void Spell_Setup(oCNpc* npc, zCVob* vob) {XCALL(0x0046F800);};
	void Spell_Invest(void) {XCALL(0x0046F990);};
	void Spell_Cast(void) {XCALL(0x0046FC00);};
	oCItem* GetSpellItem(int spellID) {XCALL(0x00472E20);};
	int GetSelectedSpellNr() {XCALL(0x00470B10);};
	void Open(int) {XCALL(0x004702A0);};
	void KillSelectedSpell() {XCALL(0x00470DD0);};
	oCSpell* GetSelectedSpell() {XCALL(0x00470AC0);};
};

/** Insert description */
class oCNewsMemory 
{
protected:
	int				knownNews_vtbl;
public:
	zCList <oCNews> iknow;
};

/** Insert description */
struct TNpcAIState 
{
	int     index;                                      // 0x05A4 int
	int     loop;                                       // 0x05A8 int
	int     end;                                        // 0x05AC int
	int     timeBehaviour;                              // 0x05B0 int
	float   restTime;                                   // 0x05B4 zREAL
	int     phase;                                      // 0x05B8 int
	zBOOL   valid;                                      // 0x05BC zBOOL
	zSTRING name;                                       // 0x05C0 zSTRING
	float   stateTime;                                  // 0x05D4 zREAL
	int     prgIndex;                                   // 0x05D8 int
	zBOOL   isRtnState;                                 // 0x05DC zBOOL
};

/** Insert description */
struct oCNpc_States 
{
public:
	int			state_vtbl;                                     // 0x0588 
	zSTRING		state_name;                                     // 0x058C zSTRING
	oCNpc*		state_npc;                                      // 0x05A0 oCNpc*
	TNpcAIState current_state;
	TNpcAIState next_state;
	int			lastAIState;                                         // 0x061C int
	zBOOL		hasRoutine;                                          // 0x0620 zBOOL
	zBOOL		rtnChanged;                                          // 0x0624 zBOOL
	int			rtnBefore;                                           // 0x0628 oCRtnEntry*
	int			rtnNow;                                              // 0x062C oCRtnEntry*
	zCRoute*	rtnRoute;                                            // 0x0630 zCRoute*
	zBOOL		rtnOverlay;                                          // 0x0634 zBOOL
	int			rtnOverlayCount;                                     // 0x0638 int
	int			walkmode_routine;                                    // 0x063C int
	zBOOL		weaponmode_routine;                                  // 0x0640 zBOOL
	zBOOL		startNewRoutine;                                     // 0x0644 zBOOL
	int			aiStateDriven;                                       // 0x0648 int
	zVEC3		aiStatePosition;                                     // 0x064C zVEC3
	oCNpc*		parOther;                                            // 0x0658 oCNpc*
	oCNpc*		parVictim;                                           // 0x065C oCNpc*
	oCItem*		parItem;                                             // 0x0660 oCItem*
	int			rntChangeCount;    // 0x0664 int

	int StartAIState(const zSTRING& name, bool endOldState, int timeBehaviour, float timed, bool isrtnstate) {XCALL(0x006C5350);};
	zSTRING GetRoutineName() {XCALL(0x006C6C10);};
};

/** Insert description */
struct oSDamageDescriptor
{
	int				dwFieldsValid;
	zCVob*			pVobAttacker;
	oCNpc*			pNpcAttacker;
	zCVob*			pVobHit;
	oCVisualFX*		pFXHit;
	oCItem*			pItemWeapon;
	zUINT32			nSpellID;
	zUINT32			nSpellCat;
	zUINT32			nSpellLevel;
	int				enuModeDamage;
	int				enuModeWeapon;
	zUINT32			aryDamage[8];
	zREAL			fDamageTotal;
	zREAL			fDamageMultiplier;
	zVEC3			vecLocationHit;
	zVEC3			vecDirectionFly;
	zSTRING			strVisualFX;
	zREAL			fTimeDuration;
	zREAL			fTimeInterval;
	zREAL			fDamagePerInterval;
	zBOOL			bDamageDontKill;

	struct
	{					 
		zUINT32			bOnce			: 1;
		zUINT32			bFinished		: 1;
		zUINT32			bIsDead			: 1;
		zUINT32			bIsUnconscious	: 1;
		zUINT32			lReserved		: 28;
	};

	zREAL			fAzimuth;
	zREAL			fElevation;
	zREAL			fTimeCurrent;
	zREAL			fDamageReal;
	zREAL			fDamageEffective;
	zUINT32			aryDamageEffective[8];
	zCVob*			pVobParticleFX;
	zCParticleFX*	pParticleFX;
	oCVisualFX*		pVisualFX;
};

/** Insert description */
class oTRobustTrace 
{
protected:
	int				_bitfield;                                             // 0x04C4 oCNpc_oTRobustTrace_bitfield_Xxx
public:
	zVEC3			targetPos;                                             // 0x04C8 zVEC3
	zCVob*   		targetVob;                                             // 0x04D4 zCVob*
	zCVob*   		obstVob;                                               // 0x04D8 zCVob*
	float     		targetDist;                                            // 0x04DC zREAL
	float     		lastTargetDist;                                        // 0x04E0 zREAL
	float     		maxTargetDist;                                         // 0x04E4 zREAL
	float     		dirTurn;                                               // 0x04E8 zREAL
	float     		timers;                                                 // 0x04EC zREAL
	zVEC3       	dirFirst;                                              // 0x04F0 zVEC3
	float     		dirLastAngle;                                          // 0x04FC zREAL
	zCArray<oTDirectionInfo*> lastDirections;
	int				frameCtr;                                              // 0x050C int
	zVEC3			targetPosArray[5];                                     // 0x0510 zVEC3[5]
	int				targetPosCounter;                                      // 0x054C int
	int				targetPosIndex;                                        // 0x0550 int
	float			checkVisibilityTime;                                   // 0x0554 zREAL
	float			positionUpdateTime;                                    // 0x0558 zREAL
	float			failurePossibility;                                    // 0x055C zREAL
};

/** Insert description */
class oCMagFrontier 
{
public:
	oCVisualFX*		warningFX;
	oCVisualFX*		shootFX;
	oCNpc*			npc;
protected:
	int				_bitfield;
};

/** Gothic's NPC class. */
class oCNpc : public oCVob
{
public:
	int				idx;
	zSTRING			name[5];
	zSTRING			slot;															// 0x0188 zSTRING
	int				npcType;														// 0x01B0 int
	int				variousFlags;													// 0x01B4 int
	int				attribute[8];													// 0x01B8 int[NPC_ATR_MAX]
	int				protection[8];													// 0x01EC int[oEDamageIndex_MAX]
	int				damage[8];														// 0x020C int[oEDamageIndex_MAX]
	int				damagetype;														// 0x022C int
	int				guild;															// 0x0230 int
	int				level;															// 0x0234 int
	int				mission[5];														// 0x0238 int[NPC_MIS_MAX]
	int				fighttactic;													// 0x024C int
	int				fmode;															// 0x0250 int
	int				voice;															// 0x0254 int
	int				voicePitch;														// 0x0258 int
	int				mass;															// 0x025C int
	int				daily_routine;													// 0x0260 int
	int				startAIState;													// 0x0264 int
	zSTRING			spawnPoint;														// 0x0268 zSTRING
	int				spawnDelay;														// 0x027C int
	int				senses;															// 0x0280 int
	int				senses_range;													// 0x0284 int
	int				aiscripts[50];													// 0x0288 int[100]
	zSTRING			wpname;															// 0x0418 zSTRING
	zUINT32			experience_points;												// 0x042C zUINT32
	zUINT32			experience_points_next_level;									// 0x0430 zUINT32
	zUINT32			learn_points;													// 0x0434 zUINT32
//	int				bodyStateInterruptableOverride;									// 0x0438 int
	int				parserEnd;														// 0x0440 int

	int				bloodEnabled;									           // 0x0444 int
	int				bloodDistance;                                             // 0x0448 int
	int				bloodAmount;                                               // 0x044C int
	int				bloodFlow;                                                 // 0x0450 int
	zSTRING			bloodEmitter;                                              // 0x0454 zSTRING
	zSTRING			bloodTexture;                                              // 0x0468 zSTRING
	int				didHit;                                                    // 0x047C zBOOL
	int				didParade;                                                 // 0x0480 zBOOL
	int				didShoot;                                                  // 0x0484 zBOOL
	int				hasLockedEnemy;                                            // 0x0488 zBOOL
	zBOOL			isDefending;                                               // 0x048C zBOOL
	zBOOL			wasAiming;                                                 // 0x0490 zBOOL
	int				lastAction;                                                // 0x0494 oCNpc::TFAction
	oCNpc*			enemy;                                                     // 0x0498 oCNpc*
	int				speedTurn;                                                 // 0x049C zREAL
	int				foundFleePoint;                                            // 0x04A0 zBOOL
	int				reachedFleePoint;                                          // 0x04A4 zBOOL
	zVEC3			vecFlee;                                                   // 0x04A8 zVEC3
	zVEC3			posFlee;                                                   // 0x04B4 zVEC3
	void*			waypointFlee;                                              // 0x04C0 zCWaypoint*
	oTRobustTrace   rbt;
	zCList<oCNpcTimedOverlay> timedOverlays;
	zCArray<oCNpcTalent*> talents;
	int				spellMana;                                        // 0x0574 int
	int				visualFX;
	oCMagFrontier	magFrontier;
	oCNpc_States	state;
	oCNpcInventory  inventory2;										
	oCItemContainer* trader;                                          // 0x0734 oCItemContainer*
	oCNpc*			tradeNpc;                                         // 0x0738 oCNpc*
	float			rangeToPlayer;                                    // 0x073C zREAL
	zCArray<zTSoundHandle> listOfVoiceHandles;
	char			x[20];
	int				voiceIndex;                                       // 0x074C int
	//zCArray<oCVisualFX*> effectList;
	int				bitfield[5];                                      // 0x075C oCNpc_bitfieldX_Xxx
	int				instanz;										  // 0x0770 int
	zSTRING			mds_name;                                         // 0x0774 zSTRING
	zSTRING			body_visualName;                                  // 0x0788 zSTRING
	zSTRING			head_visualName;                                  // 0x079C zSTRING
	zVEC3			model_scale;                                      // 0x07B0 VEC3
	float			model_fatness;                                    // 0x07BC zREAL
	int				namenr;                                           // 0x07C0 int
	float			hpHeal;                                           // 0x07C4 zREAL
	float			manaHeal;                                         // 0x07C8 zREAL
	float			swimtime;                                         // 0x07CC zREAL
	float			divetime;                                         // 0x07D0 zREAL
	float			divectr;                                          // 0x07D4 zREAL
	zCVob*			fireVob;                                          // 0x07D8 zCVob*
	int				fireDamage;                                       // 0x07DC int
	float			fireDamageTimer;                                  // 0x07E0 zREAL
	int				attitude;                                         // 0x07E4 int
	int				tmp_attitude;                                     // 0x07E8 int
	float			attTimer;                                         // 0x07EC zREAL
	int				knowsPlayer;                                      // 0x07F0 int
	int				percList[66];                                     // 0x07F4 TNpcPerc[NPC_PERC_MAX] { int percID; int percFunc }
	int				percActive;                                       // 0x08FC int
	float			percActiveTime;                                   // 0x0900 zREAL
	float			percActiveDelta;                                  // 0x0904 zREAL
	zBOOL			overrideFallDownHeight;                           // 0x0908 zBOOL
	float			fallDownHeight;                                   // 0x090C zREAL
	int				fallDownDamage;                                   // 0x0910 int
	oCMag_Book*		mag_book;                                         // 0x0914 oCMag_Book*
	zCList<oCSpell> activeSpells;
	/*int			lastHitSpellID;                                   // 0x0920 int
	int				lastHitSpellCat;                                  // 0x0924 int*/
	zCArray<zSTRING> activeOverlays;
	int				askbox;                                           // 0x0934 oCAskBox*
	int				askYes;                                           // 0x0938 int
	int				askNo;                                            // 0x093C int
	float			canTalk;                                          // 0x0940 zREAL
	oCNpc*			talkOther;                                        // 0x0944 oCNpc*
	oCInfo*			info;                                             // 0x0948 oCInfo*
	oCNews*			news;                                             // 0x094C oCNews*
	int				curMission;                                       // 0x0950 oCMission*
	oCNewsMemory	knownNews;
	zCVob*			carry_vob;                                        // 0x0960 zCVob*
	int				interactMob;                                      // 0x0964 oCMobInter*
	oCItem*			interactItem;                                     // 0x0968 oCItem*
	int    			interactItemCurrentState;                         // 0x096C int
	int     		interactItemTargetState;                          // 0x0970 int
	int      		script_aiprio;                                    // 0x0974 int
	int     		old_script_state;                                 // 0x0978 int
	int     		human_ai;                                         // 0x097C oCAIHuman*
	int     		anictrl;                                          // 0x0980 oCAniCtrl_Human*
	int     		route;                                            // 0x0984 zCRoute*
	float    		damageMul;                                        // 0x0988 zREAL
	oCNpcMessage*	csg;                                              // 0x098C oCNpcMessage*
	oCNpcMessage*	lastLookMsg;                                      // 0x0990 oCNpcMessage*
	oCNpcMessage*	lastPointMsg;                                     // 0x0994 oCNpcMessage*
	zCArray<zCVob*> vobList;
	float    		vobcheck_time;                                    // 0x09A4 zREAL
	float    		pickvobdelay;                                     // 0x09A8 zREAL
	zCVob*    		focus_vob;                                        // 0x09AC zCVob*
	zCArray<TNpcSlot*> invSlot;
	zCArray<TNpcSlot*> tmpSlotList;
	float   		fadeAwayTime;                                     // 0x09C8 zREAL
	float   		respawnTime;                                      // 0x09CC zREAL
	float   		selfDist;                                         // 0x09D0 zREAL
	int     		fightRangeBase;                                   // 0x09D4 int
	int     		fightRangeFist;                                   // 0x09D8 int
	//int     		fightRangeG;                                      // 0x09DC int
	float    		fight_waitTime;                                   // 0x09E0 zREAL
	int     		fight_waitForAniEnd;                              // 0x09E4 zTModelAniID
	float   		fight_lastStrafeFrame;                            // 0x09E8 zREAL
	int     		soundType;                                        // 0x09EC int
	zCVob*  		soundVob;                                         // 0x09F0 zCVob*
	zVEC3   		soundPosition;                                    // 0x09F4 zVEC3
	zCPlayerGroup*  playerGroup;                                      // 0x0A00 zCPlayerGroup*

public:
	void Fake_Disable();
	void Fake_DropAllInHand();
	void Hook_SetWeaponMode2(int wm);
	void DestroyNpc();
	void SetAsPlayer();
	void ForceStandUp();
	int Hook_DoDropVob(zCVob* vob);
	int Hook_DoTakeVob(zCVob* vob);
	void Hook_SetMovLock(int); //0x00694C50
	void _SetMovLock(int);
	void Hook_OpenInventory(); //0x006BB0A0
	void _OpenInventory();
	void Hook_CloseInventory(); //0x006BB2F0
	void _CloseInventory();
	int Hook_ApplyOverlay(zSTRING &overlay); //0x0068AD40
	int _ApplyOverlay(zSTRING &overlay);
	void Hook_RemoveOverlay(zSTRING &overlay); //0x0068B040
	void _RemoveOverlay(zSTRING &overlay);
	int Hook_ApplyTimedOverlayMds(zSTRING &overlay, float time); //0x006B0C60
	int DoDropVob(zCVob* vob); //0x006A10F0
	int DoTakeVob(zCVob* vob); //0x006A0D10
	void Hook_DropUnconscious(float, oCNpc*);
	void Hook_DoShootArrow(int);
	void Hook_OnDamage_Anim(oSDamageDescriptor &);
	void Hook_OnDamage_Script(oSDamageDescriptor &); //0x00738E40

	zCModelAni* GetCurrentAni();

	void InsertActiveSpell(oCSpell*) {XCALL(0x00699CA0);};
	int HasMagic() {XCALL(0x00699FB0);};
	void _SetAsPlayer() {XCALL(0x0069EAE0);};
	static int AssessFightSound_S(zCVob*, zVEC3&, zCVob*) { XCALL(0x006B5B80); };

	oCItem* IsInInv(int,int){XCALL(0x006A4E80);};
	oCItem* IsInInv(oCItem* item, int anx = 0){XCALL(0x006A4E00);};
	void SetEnemy(oCNpc* npc){XCALL(0x00691A80);};
	oCNpc* GetNextEnemy(){XCALL(0x00691CC0);};

	void ClearInventory();
	void OpenInventory() {XCALL(0x006BB0A0);};
	void CloseInventory() {XCALL(0x006BB2F0);};
	// Potrzebna funkcja to poprawy bugów z callbackami od Inv
	bool IsInvOpen() { return *(bool*)((DWORD)0x008D81E0); };
	void SetFlag(int) {XCALL(0x0068E130);};
	oCAniCtrl_Human* GetAnictrl() {XCALL(0x00691A00);};

	void DropAllInHand(){XCALL(0x00694230);};
	void DropUnconscious(float, oCNpc*){XCALL(0x00692C10);};

	void SetHeading(float angle);
	float GetHeading();

	int DoPutInInventory(oCItem*){XCALL(0x006A15F0);};
	
	oCItem* CreateItem(zSTRING& instance, int amount);

	oCVob* GetLeftHand() {XCALL(0x006977E0);};
	oCVob* GetRightHand() {XCALL(0x00697750);};
	void SetRightHand(oCVob*) {XCALL(0x00697DC0);};
	void SetLeftHand(oCVob*) {XCALL(0x00697CC0);};
	void SetFocusVob(zCVob*) {XCALL(0x0068FF70);};

	void SetTalentSkill(int,int) {XCALL(0x0068E710);}; //pierwszy - oCNpc_Talent, drugi - oCNpc_Skill
	int GetTalentSkill(int) {XCALL(0x0068ED40);};
	void SetTalentValue(int, int) {XCALL(0x0068E370);};
	int GetTalentValue(int) {XCALL(0x0068E570);};

	zSTRING GetAnimationName();
	int GetAnimationID();

	void SetSkillWeapon(int skillID, unsigned value);
	int GetSkillWeapon(int skillID);
	
	void SetLevel(int level) { *(int*)((DWORD)this + 0x1EC) = level; };
	int GetLevel(void) { return *(int*)((DWORD)this + 0x1EC); };
	void SetExperience(int experience) { *(int*)((DWORD)this + 0x31C) = experience; };
	int GetExperience() { return *(int*)((DWORD)this + 0x31C); };
	void SetExperienceNextLevel(int experience) { *(int*)((DWORD)this + 0x320) = experience; };
	int GetExperienceNextLevel() { return *(int*)((DWORD)this + 0x320); };
	void SetLearnPoints(int lp) { *(int*)((DWORD)this + 0x324) = lp; };
	int GetLearnPoints() { return *(int*)((DWORD)this + 0x324); };

	void SetProtection(int type, int value);
	int GetProtection(int type);

	void SetOpenLock(int skillLevel, unsigned value)
	{
		if (skillLevel >= 0 && skillLevel <= 2)
		{
			SetTalentSkill(NPC_TALENT_PICKLOCK, skillLevel);
			SetTalentValue(NPC_TALENT_PICKLOCK, value);
		}
	};

	int GetOpenLockLevel() { return GetTalentSkill(NPC_TALENT_PICKLOCK); };
	int GetOpenLockValue() { return GetTalentValue(NPC_TALENT_PICKLOCK); };

	void SetPickPocket(int skillLevel, unsigned value)
	{
		if (skillLevel >= 0 && skillLevel <= 2)
		{
			SetTalentSkill(NPC_TALENT_PICKPOCKET, skillLevel);
			SetTalentValue(NPC_TALENT_PICKPOCKET, value);
		}
	};

	int GetPickPocketLevel() { return GetTalentSkill(NPC_TALENT_PICKPOCKET); };
	int GetPickPocketValue() { return GetTalentValue(NPC_TALENT_PICKPOCKET); };

	void SetMagicLvl(unsigned value) { SetTalentSkill(NPC_TALENT_MAGE, value > 6 ? 6 : value); };
	int GetMagicLvl() { return GetTalentSkill(NPC_TALENT_MAGE); };
	void SetAcrobatic(bool mode) { SetTalentSkill(NPC_TALENT_ACROBAT, mode); };
	bool GetAcrobatic() { return GetTalentSkill(NPC_TALENT_ACROBAT); };
	void SetSneak(bool mode) { SetTalentSkill(NPC_TALENT_SNEAK, mode); };
	bool GetSneak() { return GetTalentSkill(NPC_TALENT_SNEAK); };

	int ApplyOverlay(zSTRING &overlay) { XCALL(0x0068AD40); };
	void RemoveOverlay(zSTRING &overlay) { XCALL(0x0068B040); };
	int GetOverlay(zSTRING &overlay) { XCALL(0x0068D860); };
	int ApplyTimedOverlayMds(zSTRING &overlay, float time) { XCALL(0x006B0C60); };
	int UseItem(oCItem *item) { XCALL(0x00698810); };
	int StopFaceAni(zSTRING &ani) { XCALL(0x00695730); };
	// holdTime | If holdTime is -1, then ani doesn't have time limit
	// intensityPercent | Value between 0.0f - 1.0f 
	int StartFaceAni(zSTRING &name, float intensityPercent, float holdTime) { XCALL(0x00695440); };

	void OnDamage_State(oSDamageDescriptor &) { XCALL(0x00747630); };
	void OnDamage_Hit(oSDamageDescriptor &) { XCALL(0x00731410); };
	void OnDamage_Anim(oSDamageDescriptor &) { XCALL(0x00741990); };
	void OnDamage_Events(oSDamageDescriptor &) { XCALL(0x00746950); };
	void OnDamage_Condition(oSDamageDescriptor &) { XCALL(0x00737C60); };
	void OnDamage_Script(oSDamageDescriptor &) { XCALL(0x00738E40); };
	void OnDamage_EfectStart(oSDamageDescriptor &) { XCALL(0x00739A20); };
	void OnDamage_EfectEnd(oSDamageDescriptor &) { XCALL(0x0073F570); };
	void OnDamage_Sound(oSDamageDescriptor &) { XCALL(0x00746660); };
	int IsConditionValid() { XCALL(0x00691F40); };
	void StopBurn() { XCALL(0x00692500); };
	
	void SetAdditionalVisuals(zSTRING &bodyModel, int bodyTexture, int skinColor, zSTRING &headModel, int headTexture, int teethTexture, int armorTexture)
	{
		XCALL(0x00694EF0)
	};

	int StartDialogAni(){XCALL(0x006B2130);};
	//.text:00736720 ; public: void __thiscall oCNpc::CompleteHeal(void)
	/** This method heals the NPC completely.
	* @usable Ingame only
	*/
	void CompleteHeal(void)
	{
		XCALL(0x00693460)
	};

	oCAIHuman* GetHumanAI() {return *(oCAIHuman**)(DWORD)this+0x09B4; };

	//.text:00736760 ; public: virtual void __thiscall oCNpc:::DoDie(oCNpc*)
	/** This method kills a NPC.
	* @param Murderer Murderer of the victim (NULL determines, that there is no murderer)
	* @usable Ingame only	
	*/
	void DoDie(oCNpc* Murderer = NULL) 
	{ 
		XCALL(0x006934A0) 
	};

	//.text:0072FF20 ; public: int __thiscall oCNpc::GetAttribute(int)
	/** This method returns the value of a selected attribute. 
	* @param Index Attribute array index
	* @returns Value of selected attribute
	* @usable Ingame only
	*/
	int GetAttribute(zINT Index)
	{
		XCALL(0x0068D7B0);
	};

	//.text:0072FAB0 ; public: int __thiscall oCNpc::GetAttitude(class oCNpc *)
	/** This method returns the attitude towards another NPC
	* @returns NPC attitude towards "other" NPC
	* @usable Ingame only
	*/
	oCNpc_Attitude GetAttitude(oCNpc* other)
	{
		XCALL(0x0068D340);
	};

	void SetAttitude(oCNpc_Attitude){ XCALL(0x0068D410);};

	//.text:0072F690 ; public: class zSTRING __thiscall oCNpc::GetGuildName(void)
	/** This method returns the guild name of the NPC.
	* @returns Current guild's name
	* @usable Ingame only
	*/
	zSTRING GetGuildName(void)
	{
		XCALL(0x0068CF20)
	};

	//.text:0072E380 ; public: virtual int __thiscall oCNpc::GetInstance(void)
	/** This method returns the internal instance ID of the NPC (important to spawn other NPCs of this type per oCObjectFactory).
	* @usable Ingame only
	*/
	zINT GetInstance(void)
	{
		XCALL(0x0068BE50)
	};

	//.text:00739A30 ; public: int __thiscall oCNpc::GetNextWeaponMode(int, int, int)
	/** Insert description. 
	* @usable Ingame only
	*/
	int GetNextWeaponMode(int, int, int)
	{
		XCALL(0x00696640)
	};

	//.text:00736740 ; public: int __thiscall oCNpc::IsDead(void)
	/** This method returns whether the NPC is dead or not.
	* @returns Whether NPC is dead or not.
	* @usable Ingame only
	*/
	zINT IsDead(void)
	{
		XCALL(0x00693480)
	};

	//.text:00736750 ; public: int __thiscall oCNpc::IsUnconscious(void)
	/** This method returns whether the NPC is unconscious or not.
	* @returns Whether NPC is dead or not.
	* @usable Ingame only
	*/
	zINT IsUnconscious(void)
	{
		XCALL(0x00693490)
	};

	//.text:00762250 ; public: void __thiscall oCNpc::OpenInventory(int)
	/** This method opens the players inventory.
	* @param p1 Unknown
	* @usable Ingame only
	*/
	void OpenInventory(zINT p1){XCALL(0x006BB0A0)};

	void OpenScreen_Status(zINT p1)
	{
		XCALL(0x0069A400);
	};

	//.text:0073D8D0 ; public: void __thiscall oCNpc::OpenScreen_Map()
	/** This method opens the map screen.
	* @param p1 Unknown
	* @usable Ingame only
	*/
	void OpenScreen_Map()
	{
		XCALL(0x0069A340);
	};

	//.text:0073D980 ; public: void __thiscall oCNpc::OpenScreen_Status(void)
	/** This method opens the status screen.
	* @usable Ingame only
	*/
	void OpenScreen_Status(void)
	{
		XCALL(0x0069A400)
	};

	//.text:007380B0 ; public: void __thiscall oCNpc::SetMovLock(int)
	/** Insert description. 
	* @param enabled Determines whether NPC is move locked or not.
	* @usable Ingame only
	*/
	void SetMovLock(zINT enabled)
	{
		XCALL(0x00694C50);
	};

	int IsMovLock(void){XCALL(0x00694C80)};

	//.text:0072FFF0 ; public: void __thiscall oCNpc::SetAttribute(int, int)
	/** This method sets the value of a selected attribute.
	* @param Index Attribute index.
	* @param Value The value... what else?
	* @usable Ingame only
	*/
	void SetAttribute(zINT Index, zINT Value)
	{
		XCALL(0x0068D840);
	};

	//.text:00730760 ; public: void __thiscall oCNpc::SetGuild(int)
	/** This method sets the NPCs guild.
	 * @param GuildId Id of the guild
	 * @usable Ingame only
	 */
	void SetGuild(zINT GuildId)
	{
		XCALL(0x0068DFB0);
	};

	//.text:00738C40 ; public: int __thiscall oCNpc::GetWeaponMode(void)
	/** Gets the current NPCs weapon mode (mainly intended for hero)
	 * @returns Current weapon mode
	 * @usable Ingame only
	 */
	oCNpc_WeaponMode GetWeaponMode()
	{
		XCALL(0x00695820);
	};

	//.text:00738C60 ; public: void __thiscall oCNpc::SetWeaponMode2(class zSTRING const &)
	/** Sets the current NPCs weapon mode (seemingly intended for daedalus - use SetWeaponMode instead if possible)
	 * @param wm Weapon mode to set
	 * @usable Ingame only
	 */
	void SetWeaponMode2(const zSTRING& wm)
	{
		XCALL(0x00695840);
	};

	//.text:00738E80 ; public: virtual void __thiscall oCNpc::SetWeaponMode2(int)
	/** Sets the current NPCs weapon mode (seemingly intended for daedalus - use SetWeaponMode instead if possible)
	 * @param wm Weapon mode to set
	 * @usable Ingame only
	 */
	void SetWeaponMode2(oCNpc_WeaponMode wm)
	{
		XCALL(0x00695A60);
	};

	//.text:00739940 ; public: virtual void __thiscall oCNpc::SetWeaponMode(int)
	/** Sets the current NPCs weapon mode (mainly intended for hero)
	 * @param wm Weapon mode to set
	 * @usable Ingame only
	 */
	void SetWeaponMode(oCNpc_WeaponMode wm)
	{
		XCALL(0x00696550);
	};

	/** This member function returns the focus Vob.
	* @return pointer with focus Vob.
	* @usable Ingame only
	*/
	zCVob* GetFocusVob(void)
	{
		XCALL(0x0068FFC0);
	};

	/** This member function returns the focus Npc.
	* @return pointer with focus Npc.
	* @usable Ingame only
	*/
	oCNpc* GetFocusNpc(void)
	{
		XCALL(0x00690000);
	};

	/** This member function returns the current angle.
	* @return zVEC3 with current angle.
	* @usable Ingame only
	*/
	zVEC3 GetAngle(void)
	{
		return zVEC3(this->trafoObjToWorld.m[0][2], this->trafoObjToWorld.m[1][2], this->trafoObjToWorld.m[2][2]);
	};

	/** This member function sets the current angle.
	* @param x
	* @param y
	* @param z
	* @usable Ingame only
	*/
	void SetAngle(float x, float y, float z)
	{
		this->trafoObjToWorld.m[0][2] = x;
		this->trafoObjToWorld.m[1][2] = y;
		this->trafoObjToWorld.m[2][2] = z;
	};

	/** This member function returns the current position.
	* @return zVEC3 with current position.
	* @usable Ingame only
	*/
	zVEC3 GetPosition(void)
	{
		return zVEC3(this->trafoObjToWorld.m[0][3], this->trafoObjToWorld.m[1][3], this->trafoObjToWorld.m[2][3]);
	};

	/** This member function sets the current position.
	* @param x
	* @param y
	* @param z
	* @usable Ingame only
	*/
	void SetPosition(float x, float y, float z)
	{
		this->trafoObjToWorld.m[0][3] = x;
		this->trafoObjToWorld.m[1][3] = y;
		this->trafoObjToWorld.m[2][3] = z;
	};

	/** This member function delivers the name.
	* @return zSTRING with the name.
	* @usable Ingame only
	*/
	zSTRING GetName(int zbool) { XCALL(0x0068D0B0); };
	//.text:00738720 ; public: class zCModel * __thiscall oCNpc::GetModel(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	zCModel* GetModel()
	{
		XCALL(0x00695300)
	};
	
	//.text: ; public: class oCMag_Book * __thiscall oCNpc::GetSpellBook(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	oCMag_Book* GetSpellBook()
	{
		XCALL(0x0069B3C0)
	};

	//.text:00745A20 ; public: virtual void __thiscall oCNpc::Disable(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	void Disable()
	{
		XCALL(0x006A1D20)
	};

	//.text:00745D40 ; public: virtual void __thiscall oCNpc::Enable(class zVEC3 &)
	/** Insert description. 
	* @usable Ingame only
	*/
	void Enable(zVEC3& pos)
	{
		XCALL(0x006A2000)
	};

	//.text:0075E920 ; int __stdcall oCNpc__SetBodyState(int Value)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetBodyState(int Value)
	{
		XCALL(0x006B8000)
	};

	/** Insert description. 
	* @usable Ingame only
	*/
    void SetName(const zSTRING& Name)
    {
		(*(zSTRING*)((DWORD)this+0x0104)).Clear();
		(*(zSTRING*)((DWORD)this+0x0104)).Insert(0, Name);
    };

	oCNpc_States GetState()
	{
		return (*(oCNpc_States*)((DWORD)this+0x0470));
	};
	oCNpcInventory* GetInventory()
	{
		return (*(oCNpcInventory**)((DWORD)this+0x550));
	};
	//.text:006660E0 ; public: virtual void __thiscall oCNpc::OnDamage(struct oCNpc::oSDamageDescriptor &)
	/** Insert description. 
	* @usable Ingame only
	*/
	void OnDamage(oSDamageDescriptor &)
	{
		XCALL(0x00730FE0)
	};

	//.text:00739C90 ; public: void __thiscall oCNpc::Equip(class oCItem *)
	/** Insert description. 
	* @usable Ingame only
	*/
	void Equip(class oCItem *)
	{
		XCALL(0x006968F0)
	};

	//.text:0073A490 ; public: void __thiscall oCNpc::EquipArmor(class oCItem *)
	/** Insert description. 
	* @usable Ingame only
	*/
	void EquipArmor(oCItem *)
	{
		XCALL(0x00697080)
	};

	//.text:0074F0B0 ; public: void __thiscall oCNpc::EquipBestArmor(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	void EquipBestArmor(void)
	{
		XCALL(0x006AA510)
	};

	//.text:0074EF30 ; public: void __thiscall oCNpc::EquipBestWeapon(int)
	/** Insert description. 
	* @usable Ingame only
	*/
	void EquipBestWeapon(int)
	{
		XCALL(0x006AA220)
	};

	//.text:0073A310 ; public: void __thiscall oCNpc::EquipFarWeapon(class oCItem *)
	/** Insert description. 
	* @usable Ingame only
	*/
	void EquipFarWeapon(oCItem *)
	{
		XCALL(0x00696F00)
	};

	//.text:007323C0 ; public: void __thiscall oCNpc::EquipItem(class oCItem *)
	/** Insert description. 
	* @usable Ingame only
	*/
	void EquipItem(oCItem *)
	{
		XCALL(0x0068F940)
	};

	//.text:0073A030 ; public: void __thiscall oCNpc::EquipWeapon(class oCItem *)
	/** Insert description. 
	* @usable Ingame only
	*/
	void EquipWeapon(oCItem *)
	{
		XCALL(0x00696C20)
	};

	//.text:00744DD0 ; public: virtual int __thiscall oCNpc::DoDropVob(class zCVob *)
	/** Insert description. 
	* @usable Ingame only
	*/
	int _DoDropVob(zCVob *)
	{
		XCALL(0x006A10F0)
	};

	//.text:007449C0 ; public: virtual int __thiscall oCNpc::DoTakeVob(class zCVob *)
	/** Insert description. 
	* @usable Ingame only
	*/
	int _DoTakeVob(zCVob *)
	{
		XCALL(0x006A0D10)
	};

	//.text:007446B0 ; public: virtual int __thiscall oCNpc::DoShootArrow(int)
	/** Insert description. 
	* @usable Ingame only
	*/
	void DoShootArrow(int)
	{
		XCALL(0x006A09F0)
	};

	//.text:007450B0 ; public: virtual int __thiscall oCNpc::DoThrowVob(class zCVob *, float)
	/** Insert description. 
	* @usable Ingame only
	*/
	void DoThrowVob(zCVob *, float)
	{
		XCALL(0x006A13C0)
	};

	oCItem* GetEquippedArmor()
	{
		XCALL(0x006947A0);
	};

	oCItem* GetEquippedMeleeWeapon()
	{
		XCALL(0x00694580);
	};

	oCItem* GetEquippedRangedWeapon()
	{
		XCALL(0x00694690);
	};

	void UnequipItem(oCItem*)
	{
		XCALL(0x0068FBC0);
	};

	oCItem* PutInInv(int, int)
	{
		XCALL(0x006A5180);
	};

	oCItem* PutInInv(const zSTRING& instance, int amount);
	void ClearEM(){ XCALL(0x006A2610);};
	int IsMonster(){XCALL(0x0069EA30);};
	int IsHalfMonster(){XCALL(0x0069EA40);};
	int IsHuman(){XCALL(0x0069EA90);};
	int IsGoblin() {XCALL(0x0069EAA0);};
	int IsOrc() {XCALL(0x0069EAB0);};
	int IsSkeleton() {XCALL(0x0069EAD0);};
	zSTRING GetInstanceName() {XCALL(0x006A1B80);};
	// End GX addition 30 Apr 2010

	/** This method returns the current oCNpc::Hero instance
	* @usable Ingame only
	*/
	inline static oCNpc* GetHero() { return *(oCNpc**)0x0086A3DC; };
};

#undef __G2EXT_API_HEADER

#endif // __API_G2_OCNPC_H__