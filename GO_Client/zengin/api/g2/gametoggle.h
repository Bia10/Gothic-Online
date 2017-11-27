#ifndef GAMETOGGLE_H
#define GAMETOGGLE_H

#include "macros.h"
//Hooks
int Hook_Apply_Options_Video();
void Fake_HandleResultString(zSTRING str);

//Function definitions
int Apply_Options_Video();
void HandleResultString(zSTRING str);
int ConsoleEval(zSTRING& s, zSTRING& msg);
int __cdecl vidGetFPSRate();

#endif //GAMETOGGLE_H