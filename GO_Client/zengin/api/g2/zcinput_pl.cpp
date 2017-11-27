/* Gothic Online Source Code */

#include "zcinput.h"

#define PL_KEYS 47 //47
#define PL_P_KEYS 9

static char PL_KeyFirst[PL_KEYS][2] = 
{
	{'a',KEY_A}, {'c', KEY_C}, {'e',KEY_E}, {'n',KEY_N}, {'o',KEY_O}, {'l',KEY_L}, {'s',KEY_S}, {'x',KEY_X}, {'z',KEY_Z}, {'b',KEY_B},
	{'d',KEY_D}, {'f',KEY_F}, {'g',KEY_G}, {'h',KEY_H}, {'i',KEY_I}, {'j',KEY_J}, {'k',KEY_K}, {'m',KEY_M}, {'p',KEY_P}, {'q',KEY_Q},
	{'r',KEY_R}, {'t',KEY_T}, {'u',KEY_U}, {'v',KEY_V}, {'w',KEY_W}, {'y',KEY_Y}, {'1',KEY_1}, {'2',KEY_2}, {'3',KEY_3}, {'4',KEY_4},
	{'5',KEY_5}, {'6',KEY_6}, {'7',KEY_7}, {'8',KEY_8}, {'9',KEY_9}, {'0',KEY_0},
	{'(',KEY_LBRACKET},		//Kwadratowy nawias lewy
	{')',KEY_RBRACKET},		//Kwaratowy nawias prawy
	{';',KEY_SEMICOLON},	//?rednik
	{'\'',KEY_APOSTROPHE},  //Apostrof pojedynczy
	{',',KEY_COMMA},        //Przecinek
	{'.',KEY_PERIOD},       //Kropka
	{'/',KEY_SLASH},        //Slash przy kropce i przycinku
	{'\\',KEY_BACKSLASH},   //Backslash pod Backspace
	{'-',KEY_MINUS},		//Minus
	{'=',KEY_EQUALS},		//Rowna sie
	{' ',KEY_SPACE}
};

static char PL_KeySecond[PL_KEYS - 1] = 
{
	'A', 'C', 'E', 'N', 'O', 'L', 'S', 'X', 'Z', 'B', 'D', 'F', 'G', 'H', 'I', 'J', 'K', 'M', 'P', 'Q', 'R', 'T', 'U', 'V', 'W', 'Y',
    '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '{', '}', ':', '"', '<', '>', '?', '|', '_', '+'
};

static char PL_KeyThird[PL_P_KEYS] = 
{
	'¹', 'æ', 'ê', 'ñ', 'ó', '³', 'œ', 'Ÿ', '¿'
};

static char PL_KeyFourth[PL_P_KEYS] = 
{
	'¥', 'Æ', 'Ê', 'Ñ', 'Ó', '£', 'Œ', '', '¯'
};

char zCInput::GetPolishLetter(int key)
{
	if(this->KeyPressed(KEY_LSHIFT) == 0 && this->KeyPressed(KEY_RSHIFT) == 0)
	{
		switch(key)
		{
		case KEY_A: return 'a'; break;
		case KEY_B: return 'b'; break;
		case KEY_C: return 'c'; break;
		}
	}
};