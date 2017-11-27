//Re-search g1 *based on g2ext*

#ifndef __API_G2_CGAMEMANAGER_H__
#define __API_G2_CGAMEMANAGER_H__

#ifndef __G2EXT_API_HEADER
#define __G2EXT_API_HEADER
#endif  //__G2EXT_API_HEADER

#ifdef _G2EXT_COMPILE_SPACER
#error Cannot use gothic headers on spacer dll (_G2EXT_COMPILE_SPACER defined)
#endif

#include "api/g2/ztypes.h"
#include "api/g2/macros.h"
#include "api/g2/ocgame.h"

/** Insert description. */
class CGameManager
{
public:
	//GO hooks
	int Fake_PlayVideo(zSTRING Filename, int i1){ return 1; };
	void Hook_Menu(int i);
	void Hook_Done();
	//End Go hooks

	void Done(){XCALL(0x00424850);};

	//.text:00425780 ; public: int __thiscall CGameManager::ExitGame(void)
	/** This method closes Gothic. 
	* @usable Ingame only
	*/
	int ExitGame(void)
	{
		XCALL(0x00424A80);
	};

	//.text:0042B1B0 ; public: class oCGame * __thiscall CGameManager::GetGame(void)
	/** This method returns the current oCGame instance.
	* @returns Current oCGame instance.
	* @usable Ingame only
	*/
	oCGame* GetGame(void)
	{
		XCALL(0x00429520);
	};
	//.text:0042B7E0 ; public: int __thiscall CGameManager::IntroduceChapter(class zSTRING, class zSTRING, class zSTRING, class zSTRING, int)
	/** This method shows a "chapter introduction" screen.
	* @param Title Determines the chapter title
	* @param Subtitle Determines the subtitle
	* @param Texture Determines the background texture
	* @param Sound Determines which sound will be played when the introduction screen is being executed
	* @param WaitTime Determines how long the introduction screen will be shown
	* @usable Ingame only
	*/
	int IntroduceChapter(zSTRING Title, zSTRING Subtitle, zSTRING Texture, zSTRING Sound, int WaitTime)
	{
		XCALL(0x00429590);
	};

	//.text:0042B940 ; public: int __thiscall CGameManager::PlayVideo(class zSTRING)
	/** This method plays a Bink video.
	* @param Filename Filename of the video (relative to data\videos\)
	* @usable Ingame only
	*/
	int PlayVideo(zSTRING Filename, int i1)
	{
		XCALL(0x00429B80);
	};

	//.text:0042BB10 ; public: int __thiscall CGameManager::PlayVideoEx(class zSTRING, short, int)
	/** This method plays a Bink video.
	* @param Filename Filename of the video (relative to data\videos\)
	* @param ScreenBlend Determines whether the "BLACK_SCREEN" should be played after playing the video (does not execute with ExitSession is true)
	* @param ExitSession Determines whether the game should be ended after playing the video.
	* @usable Ingame only
	*/
	int PlayVideoEx(zSTRING Filename, zBOOL ScreenBlend, zBOOL ExitSession) //Can't find in g1
	{
		XCALL(0x0042BB10);
	};

	void Menu(int iA){XCALL(0x004279F0)};
	void InitScreen_Open(void){XCALL(0x00425070)};
	void GameInit(void){XCALL(0x00425900)};

	/** This method returns the current CGameManager instance
	* @usable Ingame only
	*/
	inline static CGameManager*		GetGameManager(){ return *(CGameManager**)0x0085E9E4; };
};

#undef __G2EXT_API_HEADER

#endif //__API_G2_CGAMEMANAGER_H__