/* Gothic Online ZenGin research (based on g2ext) */


#ifndef __API_G2_OCOBJECTFACTORY_H__
#define __API_G2_OCOBJECTFACTORY_H__

#ifndef __G2EXT_API_HEADER
#define __G2EXT_API_HEADER
#endif  //__G2EXT_API_HEADER

#ifdef _G2EXT_COMPILE_SPACER
#error Cannot use gothic headers on spacer dll (_G2EXT_COMPILE_SPACER defined)
#endif

#include <api/g2/ztypes.h>
#include <api/g2/macros.h>

#include <api/g2/ocnpc.h>
#include <api/g2/ocitem.h>
#include <api/g2/zcworld.h>
#include <api/g2/zcvob.h>

class zFILE;

/** Insert description. */
class oCObjectFactory
{
public:
	oCItem* CreateItem2(zSTRING& instance, zVEC3 pos, int amount);

	zCVob* CreateVob(zSTRING& viusalName, int colldet, zVEC3 pos, zVEC3 rotation);
	zFILE* Hook_CreateZFile(zSTRING& filename);
	//.text:0076FDE0 ; public: virtual class oCItem * __thiscall oCObjectFactory::CreateItem(int)
	/** Insert description. 
	* @usable Ingame only
	*/
	oCItem* CreateItem(zINT p1)
	{
		XCALL(0x006C8660);
	};

	zCVob* CreateMob(zSTRING& visualName, int colldet, zVEC3 pos, zVEC3 rotation, zTVobTypeVT mobType);

	//.text:0076FD20 ; public: virtual class oCNpc * __thiscall oCObjectFactory::CreateNpc(int)
	/** Insert description. 
	* @usable Ingame only
	*/
	oCNpc* CreateNpc(zINT p1)
	{
		XCALL(0x006C8560);
	};

	//.text:0076FCA0 ; public: virtual class zCWorld * __thiscall oCObjectFactory::CreateWorld(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	zCWorld* CreateWorld(void)
	{
		XCALL(0x006C84D0);
	};
	
	zFILE* CreateZFile(zSTRING& filename)
	{
		XCALL(0x0058BD60);
	};

	/** This method returns the current oCObjectFactory instance
	* @usable Ingame only
	*/
	inline static oCObjectFactory* GetFactory(void) { return *(oCObjectFactory**)0x00873F88; };
};

#undef __G2EXT_API_HEADER

#endif // __API_G2_OCOBJECTFACTORY_H__