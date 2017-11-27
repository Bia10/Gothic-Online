#include "..\\..\\..\\stdafx.h"

//Blokowanie opcji nowa gra, wczytaj grê i zapisz grê
zSTRING zCOption::Hook_ReadString(const zSTRING& p1, const char* p2, const char* p3)
{
	pMemLib->RemoveHook(0x0045D080);

	zSTRING result;	
	if(strcmp(p2, "menuAction") == 0)
	{
		result = this->ReadString(p1, p2, p3);
		if(strcmp(result.ToChar(), "NEW_GAME") == 0 )/*|| //BO COOP
			strcmp(result.ToChar(), "SAVEGAME_LOAD") == 0 ||
			strcmp(result.ToChar(), "SAVEGAME_SAVE") == 0)*/
		{
			result = zSTRING("RESUME_GAME");
		}

	}
	else
		result = this->ReadString(p1, p2, p3);

	pMemLib->ImportHook(0x0045D080, sizeof(zSTRING(zCOption::*)(const zSTRING&, const char*, const char*)), &zCOption::Hook_ReadString);

	return result;
};