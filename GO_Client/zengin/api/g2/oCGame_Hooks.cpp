#include "..\\..\\..\\stdafx.h"

void oCGame::Hook_Render()
{
	pMemLib->RemoveHook(0x0063DBE0);
		this->Render(); //Wywo³anie oryginalnej funkcji
		this->Unpause(); //Zapobieganie pauzowaniu gry
		//Wywo³anie rendera od Gothic Online
		core.GetRender() -> Render();
	pMemLib->ImportHook(0x0063DBE0, sizeof(void(oCGame::*)(void)), &oCGame::Hook_Render);
};

int oCGame::Hook_HandleEvent(int key)
{
	pMemLib->RemoveHook(0x0065EEE0);
	int result = 1;

	if (core.GetNetwork()->IsConnected())
	{
		//First callback
		if( scr.GetScriptKeys()->IsKeyEnabled(key) == true )
			scr.GetScriptKeys()->KeyEvent(key);

		if (scr.GetScriptVars()->isKeyEnabled)
		{
			CChat* chat = core.GetChat();
			if (chat->IsInputActive() == false)
			{
				// Key 50 = M
				// Key 1  = ESC
				if (key != 50 && (scr.GetScriptVars()->isInterfaceEnabled || !scr.GetScriptVars()->isInterfaceEnabled && key != 1) && scr.GetScriptKeys()->IsKeyEnabled(key) == true)
					result = this->HandleEvent(key);
				chat->KeyEvent(key); //Open
			}
			else
			{
				chat->KeyEvent(key);
				result = 1;
			}
		}
	}
	else
		result = this->HandleEvent(key);
	
	pMemLib->ImportHook(0x0065EEE0, sizeof(int(oCGame::*)(int)), &oCGame::Hook_HandleEvent);

	return result;
};


void oCGame::Hook_ChangeLevel(zSTRING const & map1, const zSTRING & map2)
{
	pMemLib->RemoveHook(0x0063CD60);
	DLOG("oCGame::Hook_ChangeLevel(%s, %s)", zSTRING(map1).ToChar(), zSTRING(map2).ToChar());
		if( core.IsLateHooksInitiated() == true)
			core.DeInitializeLateHooks();	
		CNetwork* net = core.GetNetwork();
		if( net->IsInitiated() == true && net->IsConnected() == true )
		{
			playerManager.DestroyAllPlayers();
			playerManager.GetLocalPlayer()->SendChangeLevel(RakString(zSTRING(map1).ToChar()));
		}
		this->ChangeLevel(map1, map2);
	pMemLib->ImportHook(0x0063CD60, sizeof(void(oCGame::*)(const zSTRING&, const zSTRING&)), &oCGame::Hook_ChangeLevel);
};

void oCGame::Hook_EnterWorld(oCNpc *npc, int i, const zSTRING & str)
{
	pMemLib->RemoveHook(0x0063EAD0);
	DLOG("oCGame::Hook_EnterWorld(npc, %d, %s)", i, zSTRING(str).ToChar());
	this->EnterWorld(npc,i,str);
	if( core.IsLateHooksInitiated() == false )
		core.InitializeLateHooks();
	CNetwork* n = core.GetNetwork();
	if( n->IsInitiated() == true && n->IsConnected() == true )
	{
		if( npc == oCNpc::GetHero() )
			playerManager.GetLocalPlayer()->SendEnterWorld();
	}
	zSTRING out;
	ConsoleEval(zSTRING("ZFOGZONE"), out); //Wy³¹czenie "mg³y" - poprawa grafiki
	pMemLib->ImportHook(0x0063EAD0, sizeof(void(oCGame::*)(oCNpc*,int,const zSTRING&)), &oCGame::Hook_EnterWorld);
};

void oCGame::Fake_LoadSavegame(int a, int b)
{
#ifdef COOP
	if (scr.GetScriptVars()->isSavingActive)
	{
		pMemLib->RemoveHook(0x0063C2A0);
		if( core.IsLateHooksInitiated() == true)
			core.DeInitializeLateHooks();

		playerManager.DestroyAllNpcs();
		this->LoadSavegame(a,b);
		playerManager.CreateAllNpcs();

		if( core.IsLateHooksInitiated() == false )
			core.InitializeLateHooks();
		pMemLib->ImportHook(0x0063C2A0, sizeof(void(oCGame::*)(int,int)), &oCGame::Fake_LoadSavegame); 
	}
#endif //COOP
};

void oCGame::Fake_WriteSavegame(int a, int b)
{
#ifdef COOP
	if (scr.GetScriptVars()->isSavingActive)
	{
		pMemLib->RemoveHook(0x0063AD80);
		if( core.IsLateHooksInitiated() == true)
			core.DeInitializeLateHooks();	
		playerManager.DestroyAllNpcs();
		this->WriteSavegame(a,b);
		playerManager.CreateAllNpcs();
		if( core.IsLateHooksInitiated() == false )
			core.InitializeLateHooks();
		pMemLib->ImportHook(0x0063AD80, sizeof(void(oCGame::*)(int,int)), &oCGame::Fake_WriteSavegame);
	}
#endif //COOP
};