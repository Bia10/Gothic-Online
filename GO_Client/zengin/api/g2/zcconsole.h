/* Gothic Online ZenGin research (based on g2ext) */



#ifndef __API_G2_ZCCONSOLE_H__
#define __API_G2_ZCCONSOLE_H__

#ifndef __G2EXT_API_HEADER
#define __G2EXT_API_HEADRE
#endif  //__G2EXT_API_HEADER

#ifdef _G2EXT_COMPILE_SPACER
#error Cannot use gothic headers on spacer dll (_G2EXT_COMPILE_SPACER defined)
#endif

#include "api/g2/ztypes.h"
#include "api/g2/macros.h"
#include "api/g2/zcinputcallback.h"

class zCWorld;
class zCParser;

/** Insert description. */
class zCConsole : public zCInputCallback
{
private:
	zSTRING unk;
	zSTRING unk2;
	zSTRING result;
	char m_datab[256]; // TODO: Get size
public:
	//.text:007823E0 ; public: class zCWorld * __thiscall zCConsole::GetWorld(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	zCWorld* GetWorld() { XCALL(0x006D9240); };

	//.text:00782400 ; public: class zCParser * __thiscall zCConsole::GetParser(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	zCParser* GetParser(void) { XCALL(0x006D9260); };

	//.text:00783890 ; public: int __thiscall zCConsole::IsVisible(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	int IsVisible(void) { XCALL(0x006DA710); };

	//.text:007837A0 ; public: void __thiscall zCConsole::Toggle(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	void Toggle(void) { XCALL(0x006DA620); };

	//.text:007836B0 ; public: void __thiscall zCConsole::Hide(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	void Hide(void) { XCALL(0x006DA530); };

	//.text:00783460 ; public: void __thiscall zCConsole::Show(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	void Show(void) { XCALL(0x006DA2D0); };

	//.text:00784860 ; public: int __thiscall zCConsole::Evaluate(class zSTRING const &)
	/** Insert description. 
	* @usable Ingame only
	*/
	int	Evaluate(const zSTRING& in) { XCALL(0x006DB5D0); };

	//.text:007844B0 ; private: void __thiscall zCConsole::Eval(class zSTRING const &)
	/** Insert description. 
	* @usable Ingame only
	*/
	void Eval(const zSTRING& in) { XCALL(0x006DB220); };

	/** Insert description. 
	* @usable Ingame only
	*/
	zSTRING& GetResult(void) { return this->result; };

	//.text:007838E0 ; public: void __thiscall zCConsole::Update(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	void Update(void) { XCALL(0x006DA760); };

	//.text:00784F80 ; public: void __thiscall zCConsole::AddEvalFunc(int (__cdecl *)(class zSTRING const &, class zSTRING &))
	/** Insert description. 
	* @usable Ingame only
	*/
	void AddEvalFunc(int (__cdecl *)(zSTRING& zCommand, zSTRING& zReturn)) { XCALL(0x006DBCA0); };

	//.text:00782C00 ; public: int __thiscall zCConsole::AutoCompletion(class zSTRING &)
	/** Insert description. 
	* @usable Ingame only
	*/
	int AutoCompletion(zSTRING& str) { XCALL(0x006D9A70); };

	//.text:00782AE0 ; public: void __thiscall zCConsole::Register(class zSTRING const &, class zSTRING const &)
	/** Insert description. 
	* @usable Ingame only
	*/
	void Register(const zSTRING& zCommand, const zSTRING& zDesc) { XCALL(0x006D9940); };

	/** This method returns the current zCConsole instance
	* @usable Ingame only
	*/
	inline static zCConsole* GetConsole() { return (zCConsole*)0x008DC688; };
};

#undef __G2EXT_API_HEADER

#endif // __API_G2_ZCCONSOLE_H__