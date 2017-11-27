#include "../stdafx.h"

#define PRIORITY_AMOUNT 3

static const char PRIORITY[][30] =
{
	"UNRELIABLE",
	"RELIABLE",
	"RELIABLE_ORDERED"
};

void SVaraiable::bindGOVaraiable(HSQUIRRELVM &vm)
{
	// Priority
	for (int i = 0; i < PRIORITY_AMOUNT; ++i)
		SQ_REGISTER_GLOBAL_CONST_INT(vm, PRIORITY[i], i);
}