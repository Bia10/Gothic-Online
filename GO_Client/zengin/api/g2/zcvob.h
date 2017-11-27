/* Gothic Online ZenGin research (based on g2ext) */



#ifndef __API_G2_ZCVOB_H__
#define __API_G2_ZCVOB_H__

#ifndef __G2EXT_API_HEADER
#define __G2EXT_API_HEADER
#endif  //__G2EXT_API_HEADER

#ifdef _G2EXT_COMPILE_SPACER
#error Cannot use gothic headers on spacer dll (_G2EXT_COMPILE_SPACER defined)
#endif

#include "api/g2/ztypes.h"
#include "api/g2/macros.h"
#include "api/g2/zcobject.h"

class zCVob;
class zCVisual;
class zCWorld;
class zCAIBase;

class zCEventManager
{
private:
	zCEventManager();
	~zCEventManager();
public:
	virtual void Clear(){ XCALL(0x006DE2F0); };
};

/** Insert description. */
enum zTVobType 
{	
	VOB_TYPE_VOB,
	VOB_TYPE_LIGHT		= 1,
	VOB_TYPE_SOUND		= 2,
	VOB_TYPE_STARTPOINT = 6,
	VOB_TYPE_WAYPOINT	= 7,
	VOB_TYPE_MOB		= 128,
	VOB_TYPE_ITEM		= 129,
	VOB_TYPE_NPC		= 130
};

enum zTVobTypeVT
{
	VOB_TYPE_VT_OCMOB				= 0x007DDCFC,
	VOB_TYPE_VT_OCMOBBED			= 0x007DD1CC,
	VOB_TYPE_VT_OCMOBCONTAINER		= 0x007DD3FC,
	VOB_TYPE_VT_OCMOBDOOR			= 0x007DD8AC,
	VOB_TYPE_VT_OCMOBFIRE			= 0x007DD9E4,
	VOB_TYPE_VT_OCMOBINTER			= 0x007DDDB4,
	VOB_TYPE_VT_OCMOBITEMSLOT		= 0x007DDB04,
	VOB_TYPE_VT_OCMOBLADDER			= 0x007DD794,
	VOB_TYPE_VT_OCMOBLOCKABLE		= 0x007DD544,
	VOB_TYPE_VT_OCMOBMSG			= 0x007DDC9C,
	VOB_TYPE_VT_OCMOBSWITCH			= 0x007DD2E4,
	VOB_TYPE_VT_OCMOBWHEEL			= 0x007DD67C,
	/*******************************************/
	VOB_TYPE_VT_ZCTRIGGER			= 0x007DBF2C,
	VOB_TYPE_VT_ZCTRIGGERLIST		= 0x007DB94C,
	VOB_TYPE_VT_ZCTRIGGERTELEPORT	= 0x007DB9CC,
	VOB_TYPE_VT_ZCTRIGGERUNTOUCH	= 0x007DB67C,
	VOB_TYPE_VT_ZCTRIGGERWORLDSTART = 0x007DB8D4,
	/*******************************************/
	VOB_TYPE_VT_OCNPC				= 0x007DDF34,
	/*******************************************/
	VOB_TYPE_VT_OCVOB				= 0x0083DFE4,
	/*******************************************/
	VOB_TYPE_VT_ZCVOB				= 0x007D13CC,
	VOB_TYPE_VT_ZCVOBLIGHT			= 0x007DB534,
	VOB_TYPE_VT_ZCVOBSOUND			= 0x007DC76C,
	VOB_TYPE_VT_ZCVOBSTARTPOINT		= 0x007DEBB4,
	VOB_TYPE_VT_ZCVOBWAYPOINT		= 0x007DEA6C,
	/*******************************************/
	VOB_TYPE_VT_ERROR				= 0x77FFFFFF

};

/*
VTABLES
.rdata:0083D4D4 ; const oCMOB::`vftable'
.rdata:0083C914 ; const oCMobBed::`vftable'
.rdata:0083CB64 ; const oCMobContainer::`vftable'
.rdata:0083D054 ; const oCMobDoor::`vftable'
.rdata:0083D19C ; const oCMobFire::`vftable'
.rdata:0083D58C ; const oCMobInter::`vftable'
.rdata:0083D2CC ; const oCMobItemSlot::`vftable'
.rdata:0083CF2C ; const oCMobLadder::`vftable'
.rdata:0083CCBC ; const oCMobLockable::`vftable'
.rdata:0083D474 ; const oCMobMsg::`vftable'
.rdata:0083CA3C ; const oCMobSwitch::`vftable'
.rdata:0083CE04 ; const oCMobWheel::`vftable'

.rdata:0083D724 ; const oCNpc::`vftable'

.rdata:0083DFE4 ; const oCVob::`vftable'

.rdata:0083997C ; const zCVob::`vftable'
.rdata:00839A74 ; const zCVobLight::`vftable'
.rdata:0083ACEC ; const zCVobSound::`vftable'
.rdata:0083E4AC ; const zCVobStartpoint::`vftable'
.rdata:0083E364 ; const zCVobWaypoint::`vftable'

.rdata:0083E120 ; const oCWaypoint::`vftable'

.rdata:00832DEC ; const zCSkyControler::`vftable'
.rdata:00832CBC ; const zCSkyControler_Indoor::`vftable'
.rdata:00832D54 ; const zCSkyControler_Mid::`vftable'
.rdata:00832F54 ; const zCSkyControler_Outdoor::`vftable'

.rdata:0083131C ; const zCSndFX_MSS::`vftable'
.rdata:0083120C ; const zCSndSys_MSS::`vftable'
.rdata:0083137C ; const zCSoundFX::`vftable'
.rdata:0083A784 ; const zCSoundFXDummy::`vftable'
.rdata:00831294 ; const zCSoundSystem::`vftable'
.rdata:0083A6A4 ; const zCSoundSystemDummy::`vftable'

*/

__forceinline zTVobTypeVT GetVobType(zCVob* vob)
{
	switch(*(int*)vob)
	{
	case VOB_TYPE_VT_OCMOB:					return VOB_TYPE_VT_OCMOB; break;
	case VOB_TYPE_VT_OCMOBBED:				return VOB_TYPE_VT_OCMOBBED; break;
	case VOB_TYPE_VT_OCMOBCONTAINER:		return VOB_TYPE_VT_OCMOBCONTAINER; break;
	case VOB_TYPE_VT_OCMOBDOOR:				return VOB_TYPE_VT_OCMOBDOOR; break;
	case VOB_TYPE_VT_OCMOBFIRE:				return VOB_TYPE_VT_OCMOBFIRE; break;
	case VOB_TYPE_VT_OCMOBINTER:			return VOB_TYPE_VT_OCMOBINTER; break;
	case VOB_TYPE_VT_OCMOBITEMSLOT:			return VOB_TYPE_VT_OCMOBITEMSLOT; break;
	case VOB_TYPE_VT_OCMOBLADDER:			return VOB_TYPE_VT_OCMOBLADDER; break;
	case VOB_TYPE_VT_OCMOBLOCKABLE:			return VOB_TYPE_VT_OCMOBLOCKABLE; break;
	case VOB_TYPE_VT_OCMOBMSG:				return VOB_TYPE_VT_OCMOBMSG; break;
	case VOB_TYPE_VT_OCMOBSWITCH:			return VOB_TYPE_VT_OCMOBSWITCH; break;
	case VOB_TYPE_VT_OCMOBWHEEL:			return VOB_TYPE_VT_OCMOBWHEEL; break;
		/*******************************************/
	case VOB_TYPE_VT_ZCTRIGGER:				return VOB_TYPE_VT_ZCTRIGGER; break;
	case VOB_TYPE_VT_ZCTRIGGERLIST:			return VOB_TYPE_VT_ZCTRIGGERLIST; break;
	case VOB_TYPE_VT_ZCTRIGGERTELEPORT:		return VOB_TYPE_VT_ZCTRIGGERTELEPORT; break;
	case VOB_TYPE_VT_ZCTRIGGERUNTOUCH:		return VOB_TYPE_VT_ZCTRIGGERUNTOUCH; break;
	case VOB_TYPE_VT_ZCTRIGGERWORLDSTART:	return VOB_TYPE_VT_ZCTRIGGERWORLDSTART; break;
		/*******************************************/
	case VOB_TYPE_VT_OCNPC:					return VOB_TYPE_VT_OCNPC; break;
		/*******************************************/
	case VOB_TYPE_VT_OCVOB:					return VOB_TYPE_VT_OCVOB; break;
		/*******************************************/
	case VOB_TYPE_VT_ZCVOB:					return VOB_TYPE_VT_ZCVOB; break;
	case VOB_TYPE_VT_ZCVOBLIGHT:			return VOB_TYPE_VT_ZCVOBLIGHT; break;
	case VOB_TYPE_VT_ZCVOBSOUND:			return VOB_TYPE_VT_ZCVOBSOUND; break;
	case VOB_TYPE_VT_ZCVOBSTARTPOINT:		return VOB_TYPE_VT_ZCVOBSTARTPOINT; break;
	case VOB_TYPE_VT_ZCVOBWAYPOINT:			return VOB_TYPE_VT_ZCVOBWAYPOINT; break;
		/*******************************************/
	};

	return VOB_TYPE_VT_ERROR;
};

/** Insert description. */
class zCVob : public zCObjectNVT
{	
public:
	zCTree<zCVob>*	globalVobTreeNode;         // 0x0024 zCTree<zCVob>*
	int				lastTimeDrawn;             // 0x0028 zTFrameCtr
	DWORD			lastTimeCollected;         // 0x002C zDWORD
	zCArray<void*>	vobLeafList;
	zMAT4			trafoObjToWorld;
	zTBBox3D		bbox3D;
	zTBSphere3D		bsphere3D;
	zCArray<zCVob*> touchVobList;
	zTVobType		type;                      // 0x00B0 zTVobType
	DWORD			groundShadowSizePacked;    // 0x00B4 zDWORD
	zCWorld*		homeWorld;                 // 0x00B8 zCWorld*
	void*			groundPoly;                // 0x00BC zCPolygon* // FIXME: TYPE
	void*			callback_ai;               // 0x00C0 zCAIBase* // FIXME: TYPE
	zMAT4*			trafo;                     // 0x00C4 zMATRIX4*
	zCVisual*		visual;                    // 0x00C8 zCVisual* // FIXME: TYPE
	float			visualAlpha;               // 0x00CC zREAL
	/*float			m_fVobFarClipZScale;       // 0x00D0 zREAL
	int				m_AniMode;                 // 0x00D4 zTAnimationMode
	float			m_aniModeStrength;         // 0x00D8 zREAL
	int				m_zBias;                   // 0x00DC int*/
	void*			rigidBody;                 // 0x00E0 zCRigidBody* // FIXME: TYPE
	zCOLOR			lightColorStat;            // 0x00E4 zCOLOR
	zCOLOR			lightColorDyn;             // 0x00E8 zCOLOR
	zVEC3			lightDirectionStat;		   // 0x00EC zVEC3
	zSTRING*		vobPresetName;             // 0x00F8 zSTRING*
	int				eventManager;              // 0x00FC zCEventManager* // FIXME: TYPE
	float			nextOnTimer;               // 0x0100 zREAL
	int				bitfield[5];               // 0x0104 zCVob_bitfieldX_Xxx
	void*			m_poCollisionObjectClass;  // 0x0118 zCCollisionObjectDef*
	void*			m_poCollisionObject;       // 0x011C zCCollisionObject*

public:
	zCEventManager* __fastcall GetEM(int p1 = 0){ XCALL(0x005D49B0);};
	static zCObject* _CreateNewInstance() {XCALL(0x005D2760);};
	void SetAI(zCAIBase* ){XCALL(0x005D3730);};
	void SetSleeping(int){ XCALL(0x005D7250); };
	int GetInstance(){ XCALL(0x006D45C0); };
	zSTRING GetInstanceName(){ XCALL(0x006D45D0); };

	void SetRotation(float x, float y, float z)
	{
		this->SetRotation(zVEC3(x,y,z));
	}

	void SetRotation(zVEC3& rot)
	{
		this->ResetRotationsWorld();
		this->RotateWorldX(rot.x);
		this->RotateWorldY(rot.y);
		this->RotateWorldZ(rot.z);
	}
	//.text:0061B910 ; public: float __thiscall zCVob::GetDistanceToVob(class zCVob &)
	/** Insert description. 
	* @usable Ingame only
	*/
	float GetDistanceToVob(zCVob & pA)
	{
		XCALL(0x005EE400);
	};

	//.text:0061B970 ; public: float __thiscall zCVob::GetDistanceToVobApprox(class zCVob &)
	/** Insert description. 
	* @usable Ingame only
	*/
	float GetDistanceToVobApprox(zCVob & pA)
	{
		XCALL(0x005EE460);
	};
	//.text:0061B890 ; public: void __thiscall zCVob::GetPositionWorld(float pA &, float pA &, float pA &)const
	/** Insert description. 
	* @usable Ingame only
	*/
	void GetPositionWorld(float & pA, float & pB, float & pC)
	{
		XCALL(0x005EE380);
	};

	void RemoveVobFromWorld(void){XCALL(0x005D6670)};

	//.text:0052DC90 ; public: class zVEC3 __thiscall zCVob::GetPositionWorld(void)const
	/** Insert description. 
	* @usable Ingame only
	*/
	zVEC3 GetPositionWorld(void)
	{
		XCALL(0x0051B3C0);
	};
	//.text:006CFFD0 ; public: enum  zTVobType __thiscall zCVob::GetVobType(void)const
	/** Insert description. 
	* @usable Ingame only
	*/
	zTVobType GetVobType(void)
	{
		XCALL(0x00645020);
	};

	//.text:0061B2E0 ; int __stdcall zCVob__Move(float pA, float pA, float pA)
	/** Insert description. 
	* @usable Ingame only
	*/
	void Move(float x, float y, float z)
	{
		XCALL(0x005EDDE0);
	};

	//.text:0061B3C0 ; int __stdcall zCVob__MoveLocal(float pA, float pA, float pA)
	/** Insert description. 
	* @usable Ingame only
	*/
	void MoveLocal(float x, float y, float z)
	{
		XCALL(0x005EDEC0);
	};

	//.text:0061B350 ; public: void __thiscall zCVob::MoveWorld(float pA, float pA, float pA)
	/** Insert description. 
	* @usable Ingame only
	*/
	void MoveWorld(float x, float y, float z)
	{
		XCALL(0x005EDEC0);
	};

	//.text:0061C090 ; public: void __thiscall zCVob::ResetXZRotationsWorld(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	void ResetRotationsWorld() {XCALL(0x005EEAB0);};
	void ResetXZRotationsWorld(void)
	{
		XCALL(0x005EEB40);
	};
	//.text:0061B610 ; int __stdcall zCVob__RotateLocal(int, float pA)
	/** Insert description. 
	* @usable Ingame only
	*/
	void RotateLocal(const zVEC3& axis, float amount)
	{
		XCALL(0x005EE100);
	};

	//.text:0061B6B0 ; int __stdcall zCVob__RotateLocalX(float pA)
	/** Insert description. 
	* @usable Ingame only
	*/
	void RotateLocalX(const zVEC3& amount)
	{
		XCALL(0x005EE1A0);
	};

	//.text:0061B720 ; int __stdcall zCVob__RotateLocalY(float pA)
	/** Insert description. 
	* @usable Ingame only
	*/
	void RotateLocalY(const zVEC3& amount)
	{
		XCALL(0x005EE210);
	};

	//.text:0061B790 ; int __stdcall zCVob__RotateLocalZ(float pA)
	/** Insert description. 
	* @usable Ingame only
	*/
	void RotateLocalZ(const zVEC3& amount)
	{
		XCALL(0x005EE280);
	};

	//.text:0061B520 ; int __stdcall zCVob__RotateWorld(int, float pA)
	/** Insert description. 
	* @usable Ingame only
	*/
	void RotateWorld(const zVEC3& axis, float amount)
	{
		XCALL(0x005EE010);
	};

	//.text:0061B800 ; int __stdcall zCVob__RotateWorldX(float pA)
	/** Insert description. 
	* @usable Ingame only
	*/
	void RotateWorldX(float amount)
	{
		XCALL(0x005EE2F0);
	};

	//.text:0061B830 ; int __stdcall zCVob__RotateWorldY(float pA)
	/** Insert description. 
	* @usable Ingame only
	*/
	void RotateWorldY(float amount)
	{
		XCALL(0x005EE320);
	};

	//.text:0061B860 ; int __stdcall zCVob__RotateWorldZ(float pA)
	/** Insert description. 
	* @usable Ingame only
	*/
	void RotateWorldZ(float amount)
	{
		XCALL(0x005EE350);
	};

	//.text:006D0000 ; public: void __thiscall zCVob::SetCollDet(int)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetCollDet(int enabled)
	{
		XCALL(0x00645050);
	};

	//.text:0061CF40 ; public: void __fastcall zCVob::SetCollDetDyn(int)
	/** Insert description. 
	* @usable Ingame only
	*/
	void __fastcall SetCollDetDyn(int enabled)
	{
		XCALL(0x005EF9C0);
	};

	//.text:0061CE50 ; public: void __fastcall zCVob::SetCollDetStat(int)
	/** Insert description. 
	* @usable Ingame only
	*/
	void __fastcall SetCollDetStat(int enabled)
	{
		XCALL(0x005EF8D0);
	};

	//.text:0061BBD0 ; public: void __thiscall zCVob::SetTrafo(zMAT4 & pA)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetTrafo(zMAT4& mat)
	{
		XCALL(0x005EE6B0);
	};

	//.text:0061BC80 ; public: void __thiscall zCVob::SetTrafoObjToWorld(zMAT4 & pA)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetTrafoObjToWorld(zMAT4& mat)
	{
		XCALL(0x005EE760);
	};

	//.text:0061B0C0 ; public: void __thiscall zCVob::SetNewTrafoObjToWorld(zMAT4 & pA)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetNewTrafoObjToWorld(zMAT4& mat)
	{
		XCALL(0x005EDBC0);
	};

	//.text:0061C280 ; int __stdcall zCVob__SetHeadingYWorld(float pA)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetHeadingYWorld(const zVEC3& target)
	{
		XCALL(0x005EED30);
	};

	//.text:0061C450 ; public: void __thiscall zCVob::SetHeadingYWorld(class zCVob *)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetHeadingYWorld(zCVob* target)
	{
		XCALL(0x005EEF00);
	};

	//.text:0061C6B0 ; public: void __thiscall zCVob::SetHeadingWorld(zVEC3 & pA)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetHeadingWorld(const zVEC3& target)
	{
		XCALL(0x005EF150);
	};

	//.text:0061CBC0 ; public: void __thiscall zCVob::SetHeadingAtWorld(zVEC3 & pA)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetHeadingAtWorld(const zVEC3& target)
	{
		XCALL(0x005EF640);
	};

	//.text:0061C860 ; public: void __thiscall zCVob::SetHeadingAtLocal(zVEC3 & pA)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetHeadingAtLocal(const zVEC3& target)
	{
		XCALL(0x005EF2F0);
	};

	//.text:004042B0 ; public: virtual int __thiscall zCVob::GetScriptInstance(class zSTRING * &, int &)
	/** Insert description. 
	* @usable Ingame only
	*/
	virtual int GetScriptInstance(zSTRING * & pA, int & pB)
	{
		XCALL(0x00404170);
	};

	//.text:005FFDD0 ; public: void __thiscall zCVob::SetVobName(class zSTRING const &)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetVobName(const zSTRING & pA)
	{
		XCALL(0x005D4970);
	};

	//.text:00616B20 ; public: class zCVisual * __thiscall zCVob::GetVisual(void)const
	/** Insert description. 
	* @usable Ingame only
	*/
	zCVisual* GetVisual(void)
	{
		XCALL(0x005E9A70);
	};

	//.text:006CFFE0 ; public: void __thiscall zCVob::SetDrawBBox3D(int)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetDrawBBox3D(int pA)
	{
		XCALL(0x00645030);
	};

	//.text:006742A0 ; public: class zCWorld * __thiscall zCVob::GetHomeWorld(void)const
	/** Insert description. 
	* @usable Ingame only
	*/
	zCWorld* GetHomeWorld(void)
	{
		XCALL(0x0073F4D0);
	};

	//.text:006024F0 ; public: virtual void __thiscall zCVob::SetVisual(class zCVisual *)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetVisual(zCVisual* pA)
	{
		XCALL(0x005D6E10);
	};

	//.text:00602680 ; public: virtual void __thiscall zCVob::SetVisual(class zSTRING const &)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetVisual(const zSTRING & pA)
	{
		XCALL(0x005D6FA0);
	};

	//.text:0061BB70 ; public: void __thiscall zCVob::SetPositionWorld(class zVEC3 const &)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetPositionWorld(const zVEC3 & pA)
	{
		XCALL(0x005EE650);
	};

	//oCVob
	void SetOnFloor(zVEC3& centerPos){XCALL(0x006D43C0);};

	//.text:0061D890 ; public: int __thiscall zCVob::DetectCollision(class zMAT4 *)
	/** Insert description. 
	* @usable Ingame only
	*/
	int DetectCollision(zMAT4* mat)
	{
		XCALL(0x005F0320);
	};

	// Begin GothicX addition of 1 May 2010

	//.text:0052DCB0 ; public: class zVEC3 __thiscall zCVob::GetAtVectorWorld(void)const
	/** Insert description. 
	* @usable Ingame only
	*/
	zVEC3 GetAtVectorWorld()
	{
		XCALL(0x0051B3E0);
	};

	// End GothicX addition of 1 May 2010
	zSTRING GetVobInfo() {XCALL(0x005D6AE0);};

	zVEC3 GetVobPosition()
	{
		return zVEC3(this->trafoObjToWorld.m[0][3], this->trafoObjToWorld.m[1][3], this->trafoObjToWorld.m[2][3]);
	};

};

#undef  __G2EXT_API_HEADER

#endif  //__API_G2_ZCVOB_H__