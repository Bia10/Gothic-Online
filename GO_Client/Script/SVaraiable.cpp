#include "..\\stdafx.h"

#define KEYS_AMOUNT 103
#define WEAPONMODES_AMOUNT 9
#define SKILL_WEAPON_AMOUNT 4
#define SKILL_LEVEL_AMOUNT 3
#define PRIORITY_AMOUNT 3
#define MOB_TYPE_AMOUNT 7

static const char KEYS[][30] =
{
	"KEY_ESCAPE",
	"KEY_1",
	"KEY_2",
	"KEY_3",
	"KEY_4",
	"KEY_5",
	"KEY_6",
	"KEY_7",
	"KEY_8",
	"KEY_9",
	"KEY_0",
	"KEY_MINUS",
	"KEY_EQUALS",
	"KEY_BACK",				//backspace
	"KEY_TAB",
	"KEY_Q",
	"KEY_W",
	"KEY_E",
	"KEY_R",
	"KEY_T",
	"KEY_Y",
	"KEY_U",
	"KEY_I",
	"KEY_O",
	"KEY_P",
	"KEY_LBRACKET",
	"KEY_RBRACKET",
	"KEY_RETURN",			//Enter on main keyboard
	"KEY_LCONTROL",
	"KEY_A",
	"KEY_S",
	"KEY_D",
	"KEY_F",
	"KEY_G",
	"KEY_H",
	"KEY_J",
	"KEY_K",
	"KEY_L",
	"KEY_SEMICOLON",
	"KEY_APOSTROPHE",
	"KEY_TILDE",			//tilde
	"KEY_LSHIFT",
	"KEY_BACKSLASH",
	"KEY_Z",
	"KEY_X",
	"KEY_C",
	"KEY_V",
	"KEY_B",
	"KEY_N",
	"KEY_M",
	"KEY_COMMA",
	"KEY_PERIOD",			//on main keyboard
	"KEY_SLASH",			//on main keyboard
	"KEY_RSHIFT",
	"KEY_MULTIPLY",			//on numeric keypad
	"KEY_LMENU",			//left Alt
	"KEY_SPACE",
	"KEY_CAPITAL",
	"KEY_F1",
	"KEY_F2",
	"KEY_F3",
	"KEY_F4",
	"KEY_F5",
	"KEY_F6",
	"KEY_F7",
	"KEY_F8",
	"KEY_F9",
	"KEY_F10",
	"KEY_NUMLOCK",
	"KEY_SCROLL",			//Scroll Lock
	"KEY_NUMPAD7",
	"KEY_NUMPAD8",
	"KEY_NUMPAD9",
	"KEY_SUBTRACT",			//on numeric keypad
	"KEY_NUMPAD4",
	"KEY_NUMPAD5",
	"KEY_NUMPAD6",
	"KEY_ADD",				// + on numeric keypad
	"KEY_NUMPAD1",
	"KEY_NUMPAD2",
	"KEY_NUMPAD3",
	"KEY_NUMPAD0",
	"KEY_DECIMAL",			// . on numeric keypad
	"KEY_F11",
	"KEY_F12",
	"KEY_NUMPADENTER",		// Enter on numeric keypad
	"KEY_RCONTROL",
	"KEY_DIVIDE",			// on numeric keypad
	"KEY_RMENU",			// right Alt
	"KEY_PAUSE",			// Pause
	"KEY_HOME",				// Home on arrow keypad
	"KEY_UP",				// UpArrow on arrow keypad
	"KEY_PRIOR",			// PgUp on arrow keypad
	"KEY_LEFT",				// LeftArrow on arrow keypad
	"KEY_RIGHT",			// RightArrow on arrow keypad
	"KEY_END",				// End on arrow keypad
	"KEY_DOWN",				// DownArrow on arrow keypad
	"KEY_NEXT",				// PgDn on arrow keypad
	"KEY_INSERT",			// Insert on arrow keypad
	"KEY_DELETE",			// Delete on arrow keypad
	"KEY_POWER",			// System Power
	"KEY_SLEEP",			// System Sleep
	"KEY_WAKE"				// System Wake
};

static const char WEAPONMODES[][30] = 
{
	"NPC_WEAPON_NONE",
	"NPC_WEAPON_FIST",
	"NPC_WEAPON_DAG",
	"NPC_WEAPON_1HS",
	"NPC_WEAPON_2HS",
	"NPC_WEAPON_BOW",
	"NPC_WEAPON_CBOW",
	"NPC_WEAPON_MAG",
	"NPC_WEAPON_MAX"
};

static const char SKILL_WEAPON[][30] =
{
	"WEAPON_1H",
	"WEAPON_2H",
	"WEAPON_BOW",
	"WEAPON_CBOW"
};

static const char SKILL_LEVEL[][30] =
{
	"SKILL_LOW",
	"SKILL_MEDIUM",
	"SKILL_MASTER"
};

static const char PROTECTION_TYPE[][30] =
{
	"PROT_WEAPON",
	"PROT_ARROW",
	"PROT_FIRE",
	"PROT_MAGIC"
};

static const char PRIORITY[][30] =
{
	"UNRELIABLE",
	"RELIABLE",
	"RELIABLE_ORDERED"
};

static const char MOB_TYPE[][30] =
{
	"MOB_BED",
	"MOB_CONTAINER",
	"MOB_DOOR",
	"MOB_INTER",
	"MOB_LADDER",
	"MOB_SWITCH",
	"MOB_WHEEL",
};

static const char HAND_TYPE[][30] =
{
	"HAND_LEFT",
	"HAND_RIGHT",
};


void SVaraiable::bindGOVaraiable(HSQUIRRELVM &vm)
{
	// Keys
	for (int i = 1; i <= KEYS_AMOUNT; ++i)
		SQ_REGISTER_GLOBAL_CONST_INT(vm, KEYS[i - 1], i);
		
	// Weapon modes
	for (int i = 0; i <= WEAPONMODES_AMOUNT; ++i)
		SQ_REGISTER_GLOBAL_CONST_INT(vm, WEAPONMODES[i], i);

	// Skill level
	for (int i = 0; i < SKILL_LEVEL_AMOUNT; ++i)
		SQ_REGISTER_GLOBAL_CONST_INT(vm, SKILL_LEVEL[i], i);

	// Skill level
	for (int i = 1; i <= SKILL_WEAPON_AMOUNT; ++i)
		SQ_REGISTER_GLOBAL_CONST_INT(vm, SKILL_WEAPON[i - 1], i);

	// Protection
	for (int i = 0; i < SKILL_WEAPON_AMOUNT; ++i)
		SQ_REGISTER_GLOBAL_CONST_INT(vm, PROTECTION_TYPE[i], i);

	// Priority
	for (int i = 0; i < PRIORITY_AMOUNT; ++i)
		SQ_REGISTER_GLOBAL_CONST_INT(vm, PRIORITY[i], i);

	// Mob types
	for (int i = 0; i < MOB_TYPE_AMOUNT; ++i)
		SQ_REGISTER_GLOBAL_CONST_INT(vm, MOB_TYPE[i], i);

	// Hand types
	for (int i = 0; i < 2; ++i)
		SQ_REGISTER_GLOBAL_CONST_INT(vm, HAND_TYPE[i], i);
}