/* Gothic Online ZenGin research (based on g2ext) */

#ifndef __API_G2_INPUTCALLBACK_H__
#define __API_G2_INPUTCALLBACK_H__

#ifndef __G2EXT_API_HEADER
#define __G2EXT_API_HEADER
#endif  //__G2EXT_API_HEADER

#ifdef _G2EXT_COMPILE_SPACER
#error Cannot use gothic headers on spacer dll (_G2EXT_COMPILE_SPACER defined)
#endif

#include "api/g2/ztypes.h"
#include "api/g2/macros.h"

/** Insert description. */
class zCInputCallback
{
public:
	//.text:007A53F0 ; public: __thiscall zCInputCallback::zCInputCallback(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	zCInputCallback::zCInputCallback(void)
	{
		XCALL(0x006FB800);
	};

	//.text:0043D4E0 ; public: virtual int __thiscall zCInputCallback::HandleEvent(int)
	/** Insert description. 
	* @usable Ingame only
	*/
	virtual int zCInputCallback::HandleEvent(int key)
	{
		XCALL(0x0043D4E0);
	};

	//.text:007A54E0 ; public: void __thiscall zCInputCallback::SetEnableHandleEvent(int)
	/** Insert description. 
	* @usable Ingame only
	*/
	void zCInputCallback::SetEnableHandleEvent(int pA)
	{
		XCALL(0x00439A60);
	};

	//.text:007A5470 ; public: void __thiscall zCInputCallback::SetHandleEventTop(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	void zCInputCallback::SetHandleEventTop(void)
	{
		XCALL(0x006FB880);
	};

	//.text:007A55C0 ; public: static void __cdecl zCInputCallback::GetInput(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	static void zCInputCallback::GetInput(void)
	{
		XCALL(0x006FB9D0);
	};

};

#undef __G2EXT_API_HEADER

#endif  //__API_G2_INPUTCALLBACK_H__