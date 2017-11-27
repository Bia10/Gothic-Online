/* Gothic Online ZenGin research (based on g2ext) */


#ifndef __G2EXT_G2_OCMOB_H__
#define __G2EXT_G2_OCMOB_H__

#ifndef __G2EXT_API_HEADER
#define __G2EXT_API_HEADER
#endif  //__G2EXT_API_HEADER

#ifdef _G2EXT_COMPILE_SPACER
#error Cannot use gothic headers on spacer dll (_G2EXT_COMPILE_SPACER defined)
#endif

static const char mobDoor[5][40] = 
{
	{"TPL_DOORDECO_V1.3DS"},
	{"EVT_TPL_DECOSTONE_01_DOORS_01.3DS"},
	{"EVT_TPL_DECOSTONE_01_DOORS_02.3DS"},
	{"DOOR_WOODEN.ASC"},
	{"DOOR_WOODEN.MDS"}
};

static const char mobBed[13][40] = 
{
	{"ORC_E_BED.3DS"},
	{"ORC_BED_01.3DS"},
	{"DT_BED_V1.3DS"},
	{"BED_1_OC.ASC"},
	{"BED_2_OC.ASC"},
	{"BEDHIGH_1_OC.ASC"},
	{"BEDHIGH_2_OC.ASC"},
	{"BEDHIGH_PSI.ASC"},
	{"BEDHIGH_PC.ASC"},
	{"BEDLOW_NC.ASC"},
	{"BEDLOW_OC.ASC"},
	{"BEDLOW_PC.ASC"},
	{"BEDLOW_PSI.ASC"}
};

static const char mobLadder[9][40] =
{
	{"LADDER_2.ASC"},
	{"LADDER_3.ASC"},
	{"LADDER_4.ASC"},
	{"LADDER_5.ASC"},
	{"LADDER_6.ASC"},
	{"LADDER_7.ASC"},
	{"LADDER_8.ASC"},
	{"LADDER_9.ASC"},
	{"LADDER_10.ASC"}
};

static const char mobInter[44][40] = 
{
	{"BENCH_1_NC.ASC"},
	{"BENCH_1_OC.ASC"},
	{"BENCH_2_OC.ASC"},
	{"BENCH_3_OC.ASC"},
	{"BENCH_THRONE.ASC"},
	{"CHAIR_1_NC.ASC"},
	{"CHAIR_1_OC.ASC"},
	{"CHAIR_1_PC.ASC"},
	{"CHAIR_2_NC.ASC"},
	{"CHAIR_2_OC.ASC"},
	{"CHAIR_3_PC.ASC"},
	{"CHAIR_3_OC.ASC"},
	{"CHAIR_THRONE.ASC"},
	{"THRONE_BIG.ASC"},
	{"BARBQ_SCAV.ASC"},
	{"HERB_PSI.ASC"},
	{"LAB_PSI.ASC"},
	{"BSANVIL_OC.ASC"},
	{"BSSHARP_OC.ASC"},
	{"BSCOOL_OC.ASC"},
	{"BSFIRE_OC.ASC"},
	{"CHESTBIG_OCCHESTLARGE.ASC"},
	{"CHESTBIG_OCCHESTMEDIUM.ASC"},
	{"CHESTSMALL_OCCHESTSMALL.ASC"},
	{"CHESTBIG_ORCMUMMY.ASC"},
	{"CHESTSMALL_OCCRATESMALL.ASC"},
	{"CHESTBIG_OCCRATELARGE.ASC"},
	{"VWHEEL_1_OC.ASC"},
	{"ORE_GROUND.ASC"},
	{"FIREPLACE_GROUND.ASC"},
	{"FIREPLACE_NCSTONE.ASC"},
	{"FIREPLACE_NCSTONE2.ASC"},
	{"FIREPLACE_ORCSTAND.ASC"},
	{"FIREPLACE_HIGH.ASC"},
	{"FIREPLACE_HIGH2.ASC"},
	{"FIREPLACE_MIDDLE.ASC"},
	{"FIREPLACE_GROUND2.ASC"},
	{"FIREPLACE_PCHIGH.ASC"},
	{"FIREPLACE_PCHIGH2.ASC"},
	{"CAULDRON_OC.ASC"},
	{"LOVEBED_OC.ASC"},
	{"BATHTUB_WOODEN.ASC"},
	{"SMOKE_WATERPIPE.ASC"}
};

namespace MobType
{
	bool IsBed(zSTRING& visual);
	bool IsDoor(zSTRING& visual);
	bool IsLadder(zSTRING& visual);
	bool IsInter(zSTRING& visual);
};

class oCMob : public zCVob
{
private:    
	zSTRING			name;
	int				bitfield;
	zSTRING			visualDestroyed;
	zSTRING			ownerStr;
	zSTRING			ownerGuildStr;
	int				owner;
	int				ownerGuild;
	int				focusNameIndex;
	zCList<zCVob>   ignoreVobList;
public:
	void SetName(const zSTRING&){XCALL(0x00704F10);};
	zSTRING GetName() { XCALL(0x0067AA50); };
};

class oCMobInter : public oCMob
{
public:
	void Hook_OnTrigger(zCVob *target, zCVob *sender);
	void Hook_OnUntrigger(zCVob *target, zCVob *sender);

	static zCObject* _CreateNewInstance() {XCALL(0x006776D0);};
	void Reset() { XCALL(0x0067D140); };
	void OnTrigger(zCVob *target, zCVob *sender) { XCALL(0x0067D300); };
	void OnUntrigger(zCVob *target, zCVob *sender) { XCALL(0x0067D5F0); };
	void SetTempState(int state) { XCALL(0x0067C330); };
	void StartInteraction(oCNpc *sender) { XCALL(0x0067FCA0); };
	void EndInteraction(oCNpc *sender, int state) { XCALL(0x0067FFD0); };
	void StopInteraction(oCNpc *sender) { XCALL(0x00680250); };
	void InterruptInteraction(oCNpc *sender) { XCALL(0x0067F360); };
	void SendStateChange(int, int) { XCALL(0x0067D8C0); };
	void StartStateChange(oCNpc *sender, int begin, int end) { XCALL(0x0067E6E0); };
	void OnTick() { XCALL(0x0067D280); };
	void OnBeginStateChange(oCNpc *, int, int) { XCALL(0x0067F2F0); };
	void OnEndStateChange(oCNpc *, int, int) { XCALL(0x0067F300); };
	int IsInteractingWith(oCNpc *sender) { XCALL(0x0067FC70); };
	int AI_UseMobToState(oCNpc *sender, int state) { XCALL(0x006804F0); };
	void SetState(bool state1, bool state2) { *(int*)((DWORD)this + 0x1DC) = state1; *(int*)((DWORD)this + 0x1D4) = state2; }
	inline int GetS1() { return *(int*)((DWORD)this + 0x1DC); }
	inline int GetS2() { return *(int*)((DWORD)this + 0x1D4); }
};

class oCMobBed : public oCMob
{
public:
	static zCObject* _CreateNewInstance() {XCALL(0x00677950);};
};

class oCMobSwitch : public oCMob
{
public:
	static zCObject* _CreateNewInstance() {XCALL(0x00677CE0);};
};

class oCMobContainer : public oCMob
{
public:
	static zCObject* _CreateNewInstance() {XCALL(0x00678210);};
};

class oCMobWheel : public oCMob
{
public:
	static zCObject* _CreateNewInstance() {XCALL(0x00678980);};
};

class oCMobLadder : public oCMob
{
public:
	static zCObject* _CreateNewInstance() {XCALL(0x00678CE0);};
};

class oCMobDoor : public oCMob
{
public:
	static zCObject* _CreateNewInstance() {XCALL(0x00679050);};
	void Open(oCNpc *sender) { XCALL(0x00679250); };
	void Close(oCNpc *sender) { XCALL(0x00679260); };
};

class oCMobFire : public oCMob
{
public:
	static zCObject* _CreateNewInstance() {XCALL(0x00679460);};
};

class oCMobItemSlot : public oCMob
{
public:
	static zCObject* _CreateNewInstance() {XCALL(0x00679890);};
};

class oCMobMsg : public oCMob
{
public:
	static zCObject* _CreateNewInstance() {XCALL(0x00679EA0);};
};


#undef __G2EXT_API_HEADER

#endif // __G2EXT_G2_OCMOB_H__