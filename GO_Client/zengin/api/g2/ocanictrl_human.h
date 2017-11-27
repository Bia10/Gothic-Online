/* Gothic Online ZenGin research (based on g2ext) */



#ifndef __OCANICTRL_HUMAN_H_INCLUDED__
#define __OCANICTRL_HUMAN_H_INCLUDED__

#ifndef __G2EXT_API_HEADER
#define __G2EXT_API_HEADER
#endif  //__G2EXT_API_HEADER

#ifdef _G2EXT_COMPILE_SPACER
#error Cannot use gothic headers on spacer dll (_G2EXT_COMPILE_SPACER defined)
#endif

#include "api/g2/ztypes.h"
#include "api/g2/zcaiplayer.h"

#define CamModNormal	zSTRING("CAMMODNORMAL");
#define CamModRun		zSTRING("CAMMODRUN");
#define CamModDialog	zSTRING("CAMMODDIALOG");
#define CamModInventory	zSTRING("CAMMODINVENTORY");
#define CamModMelee		zSTRING("CAMMODMELEE");
#define CamModMagic		zSTRING("CAMMODMAGIC");
#define CamModMeleeMult	zSTRING("CAMMODMELEEMULT");
#define CamModRanged	zSTRING("CAMMODRANGED");
#define CamModSwim		zSTRING("CAMMODSWIM");
#define CamModDive		zSTRING("CAMMODDIVE");
#define CamModJump		zSTRING("CAMMODJUMP");
#define CamModJumpUp	zSTRING("CAMMODJUMPUP");
#define CamModClimb		zSTRING("CAMMODCLIMB");
#define CamModDeath		zSTRING("CAMMODDEATH");
#define CamModLook		zSTRING("CAMMODLOOK");
#define CamModLookBack	zSTRING("CAMMODLOOKBACK");
#define CamModFocus		zSTRING("CAMMODFOCUS");
#define CamModRangedShrt zSTRING("CAMMODRANGEDSHORT");
#define CamModShoulder	zSTRING("CAMMODSHOULDER");
#define CamModFirstPerson zSTRING("CAMMODFIRSTPERSON");
#define CamModThrow		zSTRING("CAMMODTHROW");
#define CamModMobLadder zSTRING("CAMMODMOBLADDER");
#define CamModFall		zSTRING("CAMMODFALL");

class zCAICamera
{
private:
	zCAICamera(){XCALL(0x004988F0);};
	~zCAICamera() {XCALL(0x00498B60);};
public:
	static zCAICamera* GetCurrent() {XCALL(0x004988E0);};
	void SetVob(zCVob* vob){XCALL(0x00499910);};
	void SetMovementEnabled(bool enable)
	{
		if (enable == false)
		{
			GetVob()->SetAI(NULL);
			GetVob()->SetSleeping(true);
		}
		else
		{
			GetVob()->SetAI((zCAIBase*)this);
			GetVob()->SetSleeping(false);
		}
	}
	zCVob* GetVob() const {return *(zCVob**)((DWORD)this+0x98);};
	void _SetTarget(zCVob* target){XCALL(0x00499BC0);};
	void SetTarget(zCVob* target)
	{
		oCNpc* hero = *(oCNpc**)0x0086A3DC;
		_SetTarget(target);
		*(oCNpc**)0x0086A3DC = hero;
	}
	void SetMode(zSTRING& m, zCArray <zCVob *>targetList){XCALL(0x004994E0);};
	zSTRING GetMode(){XCALL(0x004997F0);};
	void ClearTargetList(){XCALL(0x0049A280);};
};

#define ANI_NUM 10
#define ANI_HITLIMB_MAX 4
#define ANI_MAX_HIT 10

enum WALKMODE {	ANI_WALKMODE_RUN		,ANI_WALKMODE_WALK	,ANI_WALKMODE_SNEAK	,
		ANI_WALKMODE_WATER		,ANI_WALKMODE_SWIM	,ANI_WALKMODE_DIVE	};

enum ACTION {  ANI_ACTION_STAND		,ANI_ACTION_WALK	,ANI_ACTION_SNEAK	,ANI_ACTION_RUN,
		ANI_ACTION_WATERWALK	,ANI_ACTION_SWIM	,ANI_ACTION_DIVE	,ANI_ACTION_CHOOSEWEAPON
	 };

enum HITTYPE { ANI_HITTYPE_NONE			,ANI_HITTYPE_FORWARD };

/** Insert description. */
class oCAniCtrl_Human : public zCAIPlayer
{
private:
	float	angle_slide1;
	float	angle_slide2;
	float	angle_heading;
	float	angle_horiz;
	float	angle_ground;

	oCNpc*  npc;
	zCVob*	targetVob;             
	zCVob*	stopTurnVob;
	int		stopTurnVobSign;          

	zCModelNodeInst* hitlimb[ANI_HITLIMB_MAX];

	int		actionMode;

	int		wmode;
	int		wmode_last;
	int		wmode_selected;
	int		changeweapon;
 
	int		walkmode;
	int		nextwalkmode; 
	int		lastRunWalkSneak;
	int		always_walk;
	int		do_jump;
	int		defaultSurfaceAlign;
	float	autoRollDirection;                 

	float	lookTargetx;                  
	float	lookTargety;               

	int		distance;
	zVEC3	hitpos;
	zSTRING limbname;
	float	paradeBeginFrame;
	float	paradeEndFrame;          

	struct 
	{
		char	canEnableNextCombo	: 1;
		char	endCombo			: 1;
		char	comboCanHit			: 1;
		char	hitPosUsed			: 1;
		char	hitGraphical		: 1;
		char	canDoCollisionFX	: 1;
	} bitfield;  

	int		comboNr;
	int		comboMax;
	float	lastHitAniFrame;      
	int		hitAniID;
	zCVob*	hitTarget;       

	typedef struct 
	{
		zTModelAniID    hitAni;                             
		int             hitOptFrame;
		int             hitEndFrame;
		int             comboStartFrame;
		int             comboEndFrame;
		int             comboDir;
	} oTComboInfo;

	oTComboInfo comboInfo[ANI_MAX_HIT]; //ANI_MAX_HIT = 10

	float anioffset_lastper;
	float anioffset_thisper;
	float anioffset;              
	int anioffset_ani;

	// *****************************************************************************************

	// Normal
	int s_dead1; int s_dead2;
	int s_hang;  int t_hang_2_stand;

	int s_run               [ANI_NUM];int t_run_2_runl      [ANI_NUM];  int t_runl_2_run    [ANI_NUM];
	int s_runl              [ANI_NUM];int t_runl_2_runr     [ANI_NUM];  int t_runr_2_runl   [ANI_NUM];
	int s_runr              [ANI_NUM];int t_runr_2_run      [ANI_NUM];
	int t_runturnl          [ANI_NUM];int t_runturnr        [ANI_NUM];
	int t_runstrafel        [ANI_NUM];int t_runstrafer      [ANI_NUM];

	int t_run_2_runbl       [ANI_NUM];int t_runbl_2_run     [ANI_NUM];
	int s_runbl             [ANI_NUM];int t_runbl_2_runbr   [ANI_NUM];  int t_runbr_2_runbl [ANI_NUM];
	int s_runbr             [ANI_NUM];int t_runbr_2_run     [ANI_NUM];

	int t_jumpb             [ANI_NUM];

	// Transitions
	int t_run_2_walk        [ANI_NUM];int t_walk_2_run      [ANI_NUM];
	int t_run_2_sneak       [ANI_NUM];int t_sneak_2_run     [ANI_NUM];

	int s_walk              [ANI_NUM];int t_walk_2_walkl    [ANI_NUM];  int t_walkl_2_walk  [ANI_NUM];
	int s_walkl             [ANI_NUM];int t_walkl_2_walkr   [ANI_NUM];  int t_walkr_2_walkl [ANI_NUM];
	int s_walkr             [ANI_NUM];int t_walkr_2_walk    [ANI_NUM];
	int t_walkturnl         [ANI_NUM];int t_walkturnr       [ANI_NUM];
	int t_walkstrafel       [ANI_NUM];int t_walkstrafer     [ANI_NUM];

	int t_walk_2_walkbl     [ANI_NUM];int t_walkbl_2_walk   [ANI_NUM];
	int s_walkbl            [ANI_NUM];int t_walkbl_2_walkbr [ANI_NUM];  int t_walkbr_2_walkbl[ANI_NUM];
	int s_walkbr            [ANI_NUM];int t_walkbr_2_walk   [ANI_NUM];

	int t_runl_2_jump       [ANI_NUM];int t_runr_2_jump     [ANI_NUM];
	int t_jump_2_runl       [ANI_NUM];

	int t_stand_2_jumpuplow; int s_jumpuplow; int t_jumpuplow_2_stand;
	int t_stand_2_jumpupmid; int s_jumpupmid; int t_jumpupmid_2_stand;

	int s_sneak             [ANI_NUM];  int t_sneak_2_sneakl    [ANI_NUM];  int t_sneakl_2_sneak    [ANI_NUM];
	int s_sneakl            [ANI_NUM];  int t_sneakl_2_sneakr   [ANI_NUM];  int t_sneakr_2_sneakl   [ANI_NUM];
	int s_sneakr            [ANI_NUM];  int t_sneakr_2_sneak    [ANI_NUM];
	int t_sneakturnl        [ANI_NUM];  int t_sneakturnr        [ANI_NUM];
	int t_sneakstrafel      [ANI_NUM];  int t_sneakstrafer      [ANI_NUM];

	int t_sneak_2_sneakbl   [ANI_NUM];  int t_sneakbl_2_sneak   [ANI_NUM];
	int s_sneakbl           [ANI_NUM];  int t_sneakbl_2_sneakbr [ANI_NUM];  int t_sneakbr_2_sneakbl [ANI_NUM];
	int s_sneakbr           [ANI_NUM];  int t_sneakbr_2_sneak   [ANI_NUM];

	int t_walkl_2_aim       [ANI_NUM];  int t_walkr_2_aim       [ANI_NUM];
	int t_walk_2_aim        [ANI_NUM];  int s_aim               [ANI_NUM];  int t_aim_2_walk    [ANI_NUM];
	int t_hitl              [ANI_NUM];  int t_hitr              [ANI_NUM];  int t_hitback       [ANI_NUM];
	int t_hitf              [ANI_NUM];  int s_hitf              [ANI_NUM];
	int t_aim_2_defend      [ANI_NUM];  int s_defend            [ANI_NUM];  int t_defend_2_aim  [ANI_NUM];
	int t_paradeL           [ANI_NUM];  int t_paradeM           [ANI_NUM];  int t_paradeS       [ANI_NUM];
	int t_hitfrun           [ANI_NUM];

	int t_stumble;  int t_stumbleb; int t_fallen_2_stand; int t_fallenb_2_stand;

	int t_walk_2_walkwl     ;int t_walkwl_2_walk        ;
	int s_walkwl            ;int t_walkwl_2_walkwr      ;   int t_walkwr_2_walkwl;
	int s_walkwr            ;int t_walkwr_2_walk;

	int t_walk_2_walkwbl    ;int t_walkwbl_2_walk       ;
	int s_walkwbl           ;int t_walkwbl_2_walkwbr    ;   int t_walkwbr_2_walkwbl;
	int s_walkwbr           ;int t_walkwbr_2_walk;

	int _s_walk             ;int _t_walk_2_walkl        ;   int _t_walkl_2_walk;
	int _s_walkl            ;int _t_walkl_2_walkr       ;   int _t_walkr_2_walkl;
	int _s_walkr            ;int _t_walkr_2_walk        ;
	int _t_turnl            ;int _t_turnr               ;
	int _t_strafel          ;int _t_strafer;        

	int _t_walk_2_walkbl    ;int _t_walkbl_2_walk       ;
	int _s_walkbl           ;int _t_walkbl_2_walkbr     ;   int _t_walkbr_2_walkbl;
	int _s_walkbr           ;int _t_walkbr_2_walk;                  

	int s_jumpstand         ;int t_stand_2_jumpstand;   int t_jumpstand_2_stand;
	int _t_jumpb            ;
	int _t_stand_2_jump     ;int _s_jump            ;   int t_jump_2_stand;
	int _t_stand_2_jumpup   ;int _s_jumpup;

	int _t_jumpup_2_falldn  ;int _t_jump_2_falldn;

	int t_walkwl_2_swimf    ;int s_swimf            ;int t_swimf_2_walkwl;
	int t_walkwbl_2_swimb   ;int s_swimb            ;int t_swimb_2_walkwbl;
	int t_swimf_2_swim      ;int s_swim             ;int t_swim_2_swimf;
	int t_swim_2_swimb      ;int t_swimb_2_swim     ;int t_warn;
	int t_swim_2_dive       ;int s_dive             ;int t_divef_2_swim;
	int t_dive_2_divef      ;int s_divef            ;int t_divef_2_dive;
	int t_dive_2_drowned    ;int s_drowned          ;
	int t_swimturnl         ;int t_swimturnr        ;
	int t_diveturnl         ;int t_diveturnr;               

	int _t_walkl_2_aim      ;int _t_walkr_2_aim     ;
	int _t_walk_2_aim       ;int _s_aim             ;int _t_aim_2_walk;
	int _t_hitl             ;int _t_hitr            ;int _t_hitback;
	int _t_hitf             ;int _t_hitfstep        ;int _s_hitf;
	int _t_aim_2_defend     ;int _s_defend          ;int _t_defend_2_aim;
	int _t_paradeL          ;int _t_paradeM         ;int _t_paradeS;
	int _t_hitfrun;

	int t_stand_2_iaim      ;int s_iaim             ;int t_iaim_2_stand;

	int t_iaim_2_idrop      ;int s_idrop            ;int t_idrop_2_stand;

	int t_iaim_2_ithrow     ;int s_ithrow           ;int t_ithrow_2_stand;

	int t_stand_2_iget      ;int s_iget             ;int t_iget_2_stand;
	int s_oget;

	int _t_stand_2_torch    ;int _s_torch           ;int _t_torch_2_stand;

	int hitani;

	int help			;int help1				;int help2;
	int s_fall          ;int s_fallb            ;int s_fallen          ;int s_fallenb;     int s_falldn;
	int _t_runl_2_jump  ;int _t_runr_2_jump     ;int _t_jump_2_runl;
	int s_look;int s_point;
	int dummy1;int dummy2;int dummy3;int dummy4;
	int s_weapon[ANI_NUM];
	int togglewalk;

	int t_stand_2_cast;
	int s_cast; 
	int t_cast_2_shoot;
	int t_cast_2_stand;
	int s_shoot;
	int t_shoot_2_stand;

	int dummyLastVar;
	public:
		void ShowWeaponTrail(){ XCALL(0x00627330);};
		void CreateHit(zCVob* vob){ XCALL(0x00627C80);};
		void HitInterrupt() { XCALL(0x006280C0); };
		int IsWalking(){ XCALL(0x006257E0);};
		int GetActionMode() { XCALL(0x00746650);};
		void _Stand() { XCALL(0x0062DCF0);};
		void StopTurnAnis() { XCALL(0x00625A20);};
};

/** Insert description. */
class oCAIHuman : public oCAniCtrl_Human
{
private:
	zCList<zCVob>   ignoreVobList;
	zCAICamera*		aiCam;
	
	struct  
	{
		int	forcejump				:1;
		int	lookedAround			:1;
		int	sprintActive			:1;
		int	crawlActive				:1;
		int	showai					:1;
		int	startObserveIntruder	:1;
		int	dontKnowAniPlayed		:1;
		int	spellReleased			:1;
		int	spellCastedLastFrame	:1;
		int	eyeBlinkActivated		:1;
		int	thirdPersonFallback		:1;
	} bitfield;

	float			createFlyDamage;  //zREAL
public:
	int MagicInvestSpell() {XCALL(0x0046C330);};
	int MagicCheckSpellStates(int) {XCALL(0x0046C940);};
	void SetCamMode(const zSTRING& mode, int p2 = 0){XCALL(0x0060FE40);};
	void ChangeCamMode(const zSTRING& mode){XCALL(0x0060FB60);};
};

#undef  __G2EXT_API_HEADER

#endif  //__OCANICTRL_HUMAN_H_INCLUDED__
