/* Gothic Online ZenGin research (based on g2ext) */


#ifndef __OCVIEWPROGRESSBAR_H_INCLUDED__
#define __OCVIEWPROGRESSBAR_H_INCLUDED__

#ifndef __G2EXT_API_HEADER
#define __G2EXT_API_HEADER
#endif  //__G2EXT_API_HEADER

#ifdef _G2EXT_COMPILE_SPACER
#error Cannot use gothic headers on spacer dll (_G2EXT_COMPILE_SPACER defined)
#endif

#include "api/g2/ztypes.h"
#include "api/g2/macros.h"

/** Insert description. */
class oCViewProgressBar : public zCView
{
private:
	char _data[0x200];
public:
	//.text:0046F300 ; public: void __thiscall zCViewProgressBar::Draw(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	void Draw(void)
	{
		XCALL(0x00469F30);
	};

	//.text:0046F190 ; public: void __thiscall zCViewProgressBar::HandleChange(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	void HandleChange(void)
	{
		XCALL(0x00469E40);
	};

	//.text:0046ED40 ; public: void __thiscall zCViewProgressBar::Init(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	void Init(void)
	{
		XCALL(0x00469A60);
	};

	//.text:0046F400 ; public: void __thiscall zCViewProgressBar::ResetRange(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	void ResetRange(void)
	{
		XCALL(0x0046A050);
	};

	//.text:0046E9D0 ; public: __thiscall zCViewProgressBar::zCViewProgressBar(int, int, int, int, enum  zTviewID)
	/** Insert description. 
	* @usable Ingame only
	*/
	oCViewProgressBar(int x1, int y1, int x2, int y2, zTviewID ItemID = VIEW_ITEM)
	{
		XCALL(0x004696F0);
	};
	
	~oCViewProgressBar(void)
	{
		XCALL(0x00469900);
	};
};

#undef __G2EXT_API_HEADER

#endif  //__OCVIEWPROGRESSBAR_H_INCLUDED__