/* Gothic Online ZenGin research (based on g2ext) */


#ifndef __API_G2_OCWORLDTIMER_H__
#define __API_G2_OCWORLDTIMER_H__

#ifndef __G2EXT_API_HEADER
#define __G2EXT_API_HEADER
#endif  //__G2EXT_API_HEADER

#ifdef _G2EXT_COMPILE_SPACER
#error Cannot use gothic headers on spacer dll (_G2EXT_COMPILE_SPACER defined)
#endif

#include "api/g2/ztypes.h"

/** Insert description. */
class oCWorldTimer
{
private:
	char m_data[8];
public:
	//.text:00780DD0 ; public: int __thiscall oCWorldTimer::GetDay(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	int GetDay(void)
	{
		XCALL(0x006D7B90)
	};

	//.text:00780E80 ; public: float __thiscall oCWorldTimer::GetFullTime(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	float GetFullTime(void)
	{
		XCALL(0x006D7C40)
	};

	//.text:00780DF0 ; public: void __thiscall oCWorldTimer::GetTime(int &, int &)
	/** Insert description. 
	* @usable Ingame only
	*/
	void GetTime(int & p1, int & p2)
	{
		XCALL(0x006D7BB0)
	};

	//.text:00780EC0 ; public: class zSTRING __thiscall oCWorldTimer::GetTimeString(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	zSTRING GetTimeString(void)
	{
		XCALL(0x006D7C80)
	};

	//.text:00781280 ; public: int __thiscall oCWorldTimer::IsDay(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	int IsDay(void)
	{
		XCALL(0x006D7FD0)
	};

	//.text:00781110 ; public: int __thiscall oCWorldTimer::IsLater(int, int)
	/** Insert description. 
	* @usable Ingame only
	*/
	int IsLater(int p1, int p2)
	{
		XCALL(0x006D7E60)
	};

	//.text:00781150 ; public: int __thiscall oCWorldTimer::IsLaterEqual(int, int)
	/** Insert description. 
	* @usable Ingame only
	*/
	int IsLaterEqual(int p1, int p2) //Does not exists in g1
	{
		XCALL(0x00781150)
	};

	//.text:00781300 ; public: int __thiscall oCWorldTimer::IsNight(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	int IsNight(void) //Can't find in g1
	{
		XCALL(0x00781300)
	};

	//.text:00781190 ; public: int __thiscall oCWorldTimer::IsTimeBetween(int, int, int, int)
	/** Insert description. 
	* @usable Ingame only
	*/
	int IsTimeBetween(int p1, int p2, int p3, int p4)
	{
		XCALL(0x006D7EE0)
	};

	//.text:00780DE0 ; public: void __thiscall oCWorldTimer::SetDay(int)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetDay(int p1)
	{
		XCALL(0x006D7BA0)
	};

	//.text:00780E90 ; public: void __thiscall oCWorldTimer::SetFullTime(float)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetFullTime(float p1) //Can't find in g1
	{
		XCALL(0x00780E90)
	};

	//.text:00780E40 ; public: void __thiscall oCWorldTimer::SetTime(int, int)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetTime(int p1, int p2)
	{
		XCALL(0x006D7C00)
	};

	//.text:00780D80 ; public: void __thiscall oCWorldTimer::Timer(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	void Timer(void)
	{
		XCALL(0x006D7B40)
	};

	//.text:00780D60 ; public: __thiscall oCWorldTimer::oCWorldTimer(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	oCWorldTimer(void)
	{
		XCALL(0x006D7B20)
	};
	
	~oCWorldTimer(void)
	{
		XCALL(0x006D7B30)
	};
};

#undef __G2EXT_API_HEADER

#endif // __API_G2_OCWORLDTIMER_H__
