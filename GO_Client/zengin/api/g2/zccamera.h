/* Gothic Online ZenGin research (based on g2ext) */



#ifndef __API_G2_ZCCAMERA_H__
#define __API_G2_ZCCAMERA_H__

#ifndef __G2EXT_API_HEADER
#define __G2EXT_API_HEADER
#endif  //__G2EXT_API_HEADER

#ifdef _G2EXT_COMPILE_SPACER
#error Cannot use gothic headers on spacer dll (_G2EXT_COMPILE_SPACER defined)
#endif

#include "api/g2/ztypes.h"
#include "api/g2/macros.h"


struct zTCamVertSimple
{
	float				x,y,z;      
	zVEC2				texuv;
	zCOLOR				color;
};

enum zTCam_DrawMode 
{ 
	zCAM_DRAW_NORMAL, 
	zCAM_DRAW_NOTHING, 
	zCAM_DRAW_WIRE, 
	zCAM_DRAW_FLAT, 
	zCAM_DRAW_TEX 
};


enum { zTCAM_POLY_NUM_VERT = 4 };


/** Insert description. */
class zCCamera
{	
public:
	char dataa[164];
	zMAT4 camMatrix; // decimal 164
	char data[2108];
	zCVob* connectedVob;
	char datab[16];
	//.text:0054B660 ; int __stdcall zCCamera__AddTremor(int, float, float, int)
	/** Insert description. 
	* @usable Ingame only
	*/
	void AddTremor(const zVEC3& pos, float radius, float time, const zVEC3& amplitude) 
	{
		XCALL(0x00537140);
	};

	//.text:0054B200 ; int __stdcall zCCamera__SetFarClipZ(float)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetFarClipZ(float z)
	{
		XCALL(0x00536D30);
	};
	//.text:0054BBC0 ; public: void __thiscall zCCamera::SetRenderScreenFade(struct zCOLOR)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetRenderScreenFade(zCOLOR col)
	{
		XCALL(0x005376B0);
	};

	//.text:0054BC20 ; public: void __thiscall zCCamera::SetRenderCinemaScope(struct zCOLOR)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetRenderCinemaScope(zCOLOR col)
	{
		XCALL(0x005376D0);
	};

	//.text:0054B650 ; public: void __thiscall zCCamera::StopTremor(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	void StopTremor(void) //Can't find in g1
	{
		XCALL(0x0054B650);
	};

	//.text:0054A6A0 ; public: class zMAT4 const & __thiscall zCCamera::GetTransform(enum  zTCamTrafoType)
	/** Insert description. 
	* @usable Ingame only
	*/
	static zMAT4* GetMatrix(void)
	{
		return (zMAT4*)((int)(*(zCCamera**)0x00873240)+0x148); //may not work in g1
	};

	/** Insert description. 
	* @usable Ingame only
	*/
	static inline zCCamera* GetCamera(void)
	{
		return *(zCCamera**)0x00873240;
	};

	static inline zVEC3* GetActiveCameraPos()
	{
		return *(zVEC3**)0x00873234;
	};

	//V0ID's addition
	void UpdateViewport(void){ XCALL(0x00536850) }; //Cos jak render
	zCCamera(){ XCALL(0x00535DE0) };
	~zCCamera(){ XCALL(0x005360C0) };
	void Activate(void){ XCALL(0x005364C0) };
	void CreateProjectionMatrix(zMAT4&, float, float, float){ XCALL(0x005365D0) };
	void Project(const zVEC3* vec, int &i1, int &i2){ XCALL(0x005606D0) };
	//End V0ID's addition
};

#undef __G2EXT_API_HEADER

#endif  //__API_G2_ZCCAMERA_H__