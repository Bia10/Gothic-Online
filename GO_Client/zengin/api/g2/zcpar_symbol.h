/* Gothic Online ZenGin research (based on g2ext) */


#ifndef __ZCPAR_SYMBOL_H_INCLUDED__
#define __ZCPAR_SYMBOL_H_INCLUDED__

#ifndef __G2EXT_API_HEADER
#define __G2EXT_API_HEADER
#endif  //__G2EXT_API_HEADER

#ifdef _G2EXT_COMPILE_SPACER
#error Cannot use gothic headers on spacer dll (_G2EXT_COMPILE_SPACER defined)
#endif

#include "api/g2/ztypes.h"
#include "api/g2/macros.h"

/** Insert description. */
class zCPar_Symbol
{
public:
	//.text:007A2F30 ; public: int __thiscall zCPar_Symbol::GetOffset(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	void* GetOffset()
	{
		XCALL(0x006F9410);
	};

	//.text:007A1DC0 ; public: void * __thiscall zCPar_Symbol::GetInstanceAdr(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	void* GetInstanceAdr()
	{
		XCALL(0x006F84C0);
	};

public:
	zSTRING			name;
	zCPar_Symbol*	next;

	union
	{
		void*		data_ptr;
		int*		data_pint;
		float*		data_pfloat;
		zSTRING*	data_pstring;
		int			data_int;
		float		data_float;
	} content;

	int offset;

	int bitfield; 
	int filenr; 
	int line;
	int line_anz;
	int pos_beg;
	int pos_anz;

	zCPar_Symbol* parent;
};

#undef __G2EXT_API_HEADER

#endif //__ZCPAR_SYMBOL_H_INCLUDED__