/* Gothic Online ZenGin research (based on g2ext) */


#ifndef __API_G2_ZCRENDERER_H__
#define __API_G2_ZCRENDERER_H__

#ifndef __G2EXT_API_HEADER
#define __G2EXT_API_HEADER
#endif  //__G2EXT_API_HEADER

#ifdef _G2EXT_COMPILE_SPACER
#error Cannot use gothic headers on spacer dll (_G2EXT_COMPILE_SPACER defined)
#endif

#include "api/g2/ztypes.h"
#include "api/g2/macros.h"
#include "dx7sdk/inc/d3d.h"
#include "dx7sdk/inc/ddraw.h"

class zCVob;
class oCWorld;
class zCCamera;

struct zTRenderContext
{
	int val; // was FFx4 in zcoutdoor
	zCVob* Vob;
	oCWorld* World;
	zCCamera* Cam;
};

enum zTRnd_FogMode
{
};


/** Gothic's Direct3D 7 renderer class. */
class zCRenderer
{
private:
	char m_data[1024];
public:
	/** This method returns the current DirectDraw instance 
	* @usable Ingame only
	*/
	inline static IDirectDraw7* GetDirectDraw(void) { return *(IDirectDraw7**)0x00929D54; };

	/** This method returns the current Direct3D7 instance
	* @usable Ingame only
	*/
	inline static IDirect3D7* GetDirect3D(void) { return *(IDirect3D7**)0x00929D58; };

	/** This method returns the current Direct3D device instance
	* @usable Ingame only
	*/
	inline static IDirect3DDevice7* GetDirect3DDevice(void) { return *(IDirect3DDevice7**)0x00929D5C; };

	/** This method returns the current zCRenderer instance
	* @usable Ingame only
	*/
	inline static zCRenderer* GetRenderer()	{ return *(zCRenderer**)0x008C5ED0; };
};



#undef __G2EXT_API_HEADER

#endif //__API_G2_ZCRENDERER_H__