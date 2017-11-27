/* Gothic Online Source Code */

#include "zcinput.h"

char zCInput::GetLetter(int key)
{
	if(this->KeyPressed(KEY_RMENU) != 0 )
	{
		if( this->KeyPressed(KEY_LSHIFT) == 0 && this->KeyPressed(KEY_RSHIFT) == 0 )
		{
			switch(key)
			{
			case KEY_A: return '¹'; break;
			case KEY_E: return 'ê'; break;
			case KEY_O: return 'ó'; break;
			case KEY_S: return 'œ'; break;
			case KEY_L: return '³'; break;
			case KEY_Z: return '¿'; break;
			case KEY_X: return 'Ÿ'; break;
			case KEY_C: return 'æ'; break;
			case KEY_N: return 'ñ'; break;
			default: return NULL; break;
			}
		}
		else if( this->KeyPressed(KEY_LSHIFT) == 1 || this->KeyPressed(KEY_RSHIFT) == 1 )
		{
			switch(key)
			{
			case KEY_A: return '¥'; break;
			case KEY_E: return 'Ê'; break;
			case KEY_O: return 'Ó'; break;
			case KEY_S: return 'Œ'; break;
			case KEY_L: return '£'; break;
			case KEY_Z: return '¯'; break;
			case KEY_X: return ''; break;
			case KEY_C: return 'Æ'; break;
			case KEY_N: return 'Ñ'; break;
			default: return NULL; break;
			}
		}
	}
	else if(this->KeyPressed(KEY_LSHIFT) == 0 && this->KeyPressed(KEY_RSHIFT) == 0 )
	{
		switch(key)
		{
		case KEY_A: return 'a'; break;
		case KEY_B: return 'b'; break;
		case KEY_C: return 'c'; break;
		case KEY_D: return 'd'; break;
		case KEY_E: return 'e'; break;
		case KEY_F: return 'f'; break;
		case KEY_G: return 'g'; break;
		case KEY_H: return 'h'; break;
		case KEY_I: return 'i'; break;
		case KEY_J: return 'j'; break;
		case KEY_K: return 'k'; break;
		case KEY_L: return 'l'; break;
		case KEY_M: return 'm'; break;
		case KEY_N: return 'n'; break;
		case KEY_O: return 'o'; break;
		case KEY_U: return 'u'; break;
		case KEY_P: return 'p'; break;
		case KEY_Q: return 'q'; break;
		case KEY_R: return 'r'; break;
		case KEY_S: return 's'; break;
		case KEY_V: return 'v'; break;
		case KEY_T: return 't'; break;
		case KEY_W: return 'w'; break;
		case KEY_Z: return 'z'; break;
		case KEY_Y: return 'y'; break;
		case KEY_X: return 'x'; break;
		case KEY_0: return '0'; break;
		case KEY_1: return '1'; break;
		case KEY_2: return '2'; break;
		case KEY_3: return '3'; break;
		case KEY_4: return '4'; break;
		case KEY_5: return '5'; break;
		case KEY_6: return '6'; break;
		case KEY_7: return '7'; break;
		case KEY_8: return '8'; break;
		case KEY_9: return '9'; break;
		case KEY_LBRACKET: return '('; break;
		case KEY_RBRACKET: return ')'; break;
		case KEY_SEMICOLON: return ';'; break;
		case KEY_APOSTROPHE: return '\''; break;
		case KEY_COMMA: return ','; break;
		case KEY_PERIOD: return '.'; break;
		case KEY_SLASH: return '/'; break;
		case KEY_BACKSLASH: return '\\'; break;
		case KEY_MINUS: return '-'; break;
		case KEY_EQUALS: return '='; break;
		case KEY_SPACE: return ' '; break;
		default: return NULL; break;
		
		}
	}
	else if(this->KeyPressed(KEY_LSHIFT) != 0 || this->KeyPressed(KEY_RSHIFT) != 0)
	{
		switch(key)
		{
		case KEY_A: return 'A'; break;
		case KEY_B: return 'B'; break;
		case KEY_C: return 'C'; break;
		case KEY_D: return 'D'; break;
		case KEY_E: return 'E'; break;
		case KEY_F: return 'F'; break;
		case KEY_G: return 'G'; break;
		case KEY_H: return 'H'; break;
		case KEY_I: return 'I'; break;
		case KEY_J: return 'J'; break;
		case KEY_K: return 'K'; break;
		case KEY_L: return 'L'; break;
		case KEY_M: return 'M'; break;
		case KEY_N: return 'N'; break;
		case KEY_O: return 'O'; break;
		case KEY_U: return 'U'; break;
		case KEY_P: return 'P'; break;
		case KEY_Q: return 'Q'; break;
		case KEY_R: return 'R'; break;
		case KEY_S: return 'S'; break;
		case KEY_V: return 'V'; break;
		case KEY_T: return 'T'; break;
		case KEY_W: return 'W'; break;
		case KEY_Y: return 'Y'; break;
		case KEY_Z: return 'Z'; break;
		case KEY_X: return 'X'; break;
		case KEY_0: return ')'; break;
		case KEY_1: return '!'; break;
		case KEY_2: return '@'; break;
		case KEY_3: return '#'; break;
		case KEY_4: return '$'; break;
		case KEY_5: return ';'; break;
		case KEY_6: return '^'; break;
		case KEY_7: return '&'; break;
		case KEY_8: return '*'; break;
		case KEY_9: return '('; break;
		case KEY_LBRACKET: return '{'; break;
		case KEY_RBRACKET: return '}'; break;
		case KEY_SEMICOLON: return ':'; break;
		case KEY_APOSTROPHE: return '"'; break;
		case KEY_COMMA: return '<'; break;
		case KEY_PERIOD: return '>'; break;
		case KEY_SLASH: return '?'; break;
		case KEY_BACKSLASH: return '|'; break;
		case KEY_MINUS: return '_'; break;
		case KEY_EQUALS: return '+'; break;
		case KEY_SPACE: return ' ';	break;
		default: return NULL; break;
		}
	}
	return NULL;
};