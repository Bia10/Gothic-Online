/* Gothic Online ZenGin research (based on g2ext) */



#ifndef __ZTIMER_H_INCLUDED__
#define __ZTIMER_H_INCLUDED__

#ifndef __G2EXT_API_HEADER
#define __G2EXT_API_HEADER
#endif  //__G2EXT_API_HEADER

#ifdef _G2EXT_COMPILE_SPACER
#error Cannot use gothic headers on spacer dll (_G2EXT_COMPILE_SPACER defined)
#endif

#include "api/g2/ztypes.h"
#include "api/g2/macros.h"

/** Insert description. */
class zCTimer
{
public:
	
	void LimitFPS(int p1)
	{
		XCALL(0x005CE6E0)
	};

	static zCTimer* GetTimer()
	{
		return (zCTimer*)0x008CF1E8;
	};

	void ResetTimer(void)
	{
		XCALL(0x005CE550)
	};

	void SetFrameTime(float)
	{
		XCALL(0x005CE620)
	};

	void SetMotionFactor(float)
	{
		XCALL(0x00607640)
	};

	void SetMaxFPS(int) //Backported from g2
	{
		__asm mov eax, [esp+4]
		__asm mov [ecx+0x24], eax
		__asm retn 4
	};

	int GetMaxFPS(void)
	{
		__asm mov eax, [ecx+0x24]
		__asm retn
	};
};

#undef __G2EXT_API_HEADER

#endif  //__ZTIMER_H_INCLUDED__
