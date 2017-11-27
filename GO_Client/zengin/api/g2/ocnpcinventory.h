/* Gothic Online ZenGin research (based on g2ext) */



#ifndef __API_G2_OCNPCINVENTORY_H__
#define __API_G2_OCNPCINVENTORY_H__

#ifndef __G2EXT_API_HEADER
#define __G2EXT_API_HEADER
#endif  //__G2EXT_API_HEADER

#ifdef _G2EXT_COMPILE_SPACER
#error Cannot use gothic headers on spacer dll (_G2EXT_COMPILE_SPACER defined)
#endif

#include "api/g2/ztypes.h"
#include "api/g2/zstring.h"

class oCNpc;
class oCItem;

/** Insert description. */
class oCNpcInventory
{
public:
	oCItemContainer inv;
	oCNpc*			owner;
	zBOOL			packAbility;
	//zCListSort<oCItem> {
	int				inventory_Compare;
	int				inventory_data;
	int				inventory_next;
	//}
	zSTRING			packString;
	int				maxSlots;

public:
	oCNpcInventory(){XCALL(0x0066B3D0);};
	virtual ~oCNpcInventory() {XCALL(0x0066BA60);};
	void ClearInventory() {XCALL(0x0066BC50);};
};

#undef __G2EXT_API_HEADER

#endif  //__API_G2_OCNPCINVENTORY_H__