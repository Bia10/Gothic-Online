/* Gothic Online ZenGin research (based on g2ext) */


#ifndef __ZCAIPLAYER_H_INCLUDED__
#define __ZCAIPLAYER_H_INCLUDED__

#ifndef __G2EXT_API_HEADER
#define __G2EXT_API_HEADER
#endif  //__G2EXT_API_HEADER

#ifdef _G2EXT_COMPILE_SPACER
#error Cannot use gothic headers on spacer dll (_G2EXT_COMPILE_SPACER defined)
#endif

#include "api/g2/ztypes.h"

class zCModel;
class zCModelNodeInst;

/** Insert description. */
enum zTSurfaceAlignMode 
{                       
	zMV_SURFACE_ALIGN_NONE  = 0, // none - like human
	zMV_SURFACE_ALIGN_NORMAL= 1, // like f.e shadowbeast*
	zMV_SURFACE_ALIGN_HIGH  = 2, // like f.e meatbugs
};

/** Insert description. */
enum zTMovementState 
{
	zMV_STATE_STAND         = 0,                
	zMV_STATE_FLY           = 1,                
	zMV_STATE_SWIM          = 2,                
	zMV_STATE_DIVE          = 3,                
};

/** Insert description. */
class zCAIPlayer : public zCObject
{
	struct zTConfig
	{
		float zMV_MIN_SPACE_MOVE_FORWARD;
		float zMV_DETECT_CHASM_SCAN_AT;
		float zMV_STEP_HEIGHT;
		float zMV_JUMP_UP_MIN_CEIL;
		float zMV_WATER_DEPTH_KNEE;
		float zMV_WATER_DEPTH_CHEST;
		float zMV_YMAX_SWIM_CLIMB_OUT;
		float zMV_FORCE_JUMP_UP;
		float zMV_YMAX_JUMPLOW; 
		float zMV_YMAX_JUMPMID;
		float zMV_MAX_GROUND_ANGLE_WALK;
		float zMV_MAX_GROUND_ANGLE_SLIDE;
		float zMV_MAX_GROUND_ANGLE_SLIDE2;
		float zMV_DCUL_WALL_HEADING_ANGLE;
		float zMV_DCUL_WALL_HORIZ_ANGLE;
		float zMV_DCUL_GROUND_ANGLE;
	} config;                 

	zCVob*		vob;
	zCModel*	model; 
	zCWorld*	world;

	zPOINT3		centerPos;
	float		feetY;
	float		headY;
	float		aboveFloor;

	int			waterLevel;

	float		velocityLen2;
	zVEC3		velocity;                 

	float		fallDownDistanceY;
	float		fallDownStartY;              

	zVEC3		slidePolyNormal;
	float		checkWaterCollBodyLen;                       
	zCModelNodeInst*  modelHeadNode;  

	int bitfield[6];


	struct zTBloodVobTrack 
	{
	zCVob*	bloodVob;
	zREAL	alpha;
	};

	zCArray<zTBloodVobTrack>  bloodVobList;

	float		bleedingPerc;       //zREAL
	zVEC3		bleedingLastPos;    //zVEC3
	float		bleedingNextDist;   //zREAL

	zCVob*		weaponTrailVob;     //zCVob*

	zCVob*		waterRingVob;       //zCVob*
	float		waterRingTimer;     //zREAL

	float		autoRollPos;         //zREAL      
	float		autoRollPosDest;     //zREAL      
	float		autoRollSpeed;       //zREAL      
	float		autoRollMaxAngle;    //zREAL

	BYTE	dummyLastVar;       //zBYTE
	zSTRING bloodDefaultTexName; //zSTRING   
};

#undef  __G2EXT_API_HEADER

#endif  //__ZCAIPLAYER_H_INCLUDED__