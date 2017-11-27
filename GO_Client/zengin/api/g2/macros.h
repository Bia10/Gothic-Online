/* Gothic Online ZenGin research (based on g2ext) */


#ifndef __API_G2_MACROS_H__
#define __API_G2_MACROS_H__

#ifndef __G2EXT_API_HEADER
#define __G2EXT_API_HEADER
#endif  //__G2EXT_API_HEADER

#ifdef _G2EXT_COMPILE_SPACER
#error Cannot use gothic headers on spacer dll (_G2EXT_COMPILE_SPACER defined)
#endif

#pragma warning(disable:4731) // -- suppress C4731:"frame pointer register 'ebp' modified by inline assembly code"

// -- call macro from GothicX (thx, Zerxes!)

#define XCALL(uAddr)			\
	__asm { mov esp, ebp	}	\
	__asm { pop ebp			}	\
	__asm { mov eax, uAddr	}	\
	__asm { jmp eax			}

#undef __G2EXT_API_HEADER

#endif //__API_G2_MACROS_H__