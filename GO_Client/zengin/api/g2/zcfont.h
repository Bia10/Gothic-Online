/* Gothic Online ZenGin research (based on g2ext) */
#ifndef __ZCFONT_H_INCLUDED__
#define __ZCFONT_H_INCLUDED__

#ifndef __G2EXT_API_HEADER
#define __G2EXT_API_HEADER
#endif  //__G2EXT_API_HEADER

#ifdef _G2EXT_COMPILE_SPACER
#error Cannot use gothic headers on spacer dll (_G2EXT_COMPILE_SPACER defined)
#endif

#include "api/g2/ztypes.h"
#include "api/g2/macros.h"

class zCFont
{
public:
	int GetFontX(zSTRING &) { XCALL(0x006E0210); };
	int GetFontY() { XCALL(0x006E0200); };
	int GetWidth(char) { XCALL(0x006E0240); };
	int GetLetterDistance() { XCALL(0x006E0250); };
};

#undef __G2EXT_API_HEADER

#endif // __ZCFONT_H_INCLUDED__