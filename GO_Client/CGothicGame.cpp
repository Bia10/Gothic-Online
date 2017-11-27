#include "stdafx.h"

CGothicGame::CGothicGame()
{
	DLOG("CGothicGame::CGothicGame()");
	bIsFirstFrame = true; //Po u�yciu tego, w renderze wys�a� pakiet o gotowo�ci clienta
};

void CGothicGame::InitGame() //Uruchamianie z hooka na pokazanie menu :)
{
	//Wczytywanie nazwy �wiata z configu
	//Uruchamianie �wiata z wy��czonymi npc'ami
	//Nawi�zanie po��czenia z serwerem i wys�anie pakietu autoryzacyjnego
	//Zmiana czasu na godzine 8:00
	DLOG("CGothicGame::InitGame()");
	oCGame* game = oCGame::GetGame();
	CChat* chat = core.GetChat();
	CConfig* config = core.GetConfig();
	CNetwork* net = core.GetNetwork();

	if( game )
	{
		game -> LoadWorldStartup(zSTRING(core.GetConfig()->GetStartWorld().C_String()));
		game -> EnterWorld(0, 1, *(zSTRING*)(0x00869978)); //zSTR_EMPTY
		oCSpawnManager* spawnManager = game -> GetSpawnManager();
		if( spawnManager )
		{
			oCSpawnManager::SetRemoveRange(2097152.0f); //Usuwanie postaci tylko na duzej odleglosci (zamiast tamtych hookow)
			spawnManager -> SetSpawningEnabled(0); //Wy��cza spawnowanie npc
		}
/*		
#ifdef DEV_MODE
	
	UINT result = WinExec("Multiplayer//GO_HS.exe",SW_SHOWNORMAL);
	switch(result)
	{
	case 0:
		MessageBox(NULL, "Out of memory", "Gothic Online", MB_OK);
		CGameManager::GetGameManager()->ExitGame(); ExitProcess(0); break;
	case ERROR_BAD_FORMAT:
		MessageBox(NULL, "Bad file format", "Gothic Online", MB_OK);
		CGameManager::GetGameManager()->ExitGame(); ExitProcess(0); break;
	case ERROR_FILE_NOT_FOUND:
		MessageBox(NULL, "File not found", "Gothic Online", MB_OK);
		CGameManager::GetGameManager()->ExitGame(); ExitProcess(0); break;
	case ERROR_PATH_NOT_FOUND:
		MessageBox(NULL, "Path not found", "Gothic Online", MB_OK);
		CGameManager::GetGameManager()->ExitGame(); ExitProcess(0); break;
	};
#endif //DEV_MODE
	*/
		game -> SetTime(0, 8, 0);

		oCNpc* hero = oCNpc::GetHero();
		if( hero )
		{
			const char* playerInstance = core.GetConfig()->GetPlayerInstance().C_String();
			if( strcmp(playerInstance, hero->GetInstanceName().ToChar()) != 0 )
			{
				zVEC3 pos = hero->GetPosition();
				oCNpc* new_npc = oCGame::GetGame()->CreateNPC(zSTRING(playerInstance),pos.x,pos.y,pos.z);
				if( new_npc )
				{
					new_npc->SetAsPlayer();
					hero->DestroyNpc();
				}
			}
		}
	
		//P�ne hooki
		if( core.IsLateHooksInitiated() == false )
			core.InitializeLateHooks();
		//Inicjalizacja czatu i kilka wiadomo�ci informacyjnych
		chat -> InitChat();
		chat -> Show(true);
		chat->AddLine(RakString("Gothic Online %s", versionString), zCOLOR(255, 196, 0, 255));
		/*//test hashlib
		wrapperfactory wf;
		hashwrapper* hl = wf.create(HL_MD5);
		std::string hash = hl->getHashFromFile(std::string("Multiplayer//GO_HS.exe"));
		delete hl;

		chat -> AddLine(RakString("GO_HS.exe: %s", hash.c_str()), zCOLOR(0,255,255,255));*/
		//Nawi�zywanie po��czenia z serwerem
		if( net->InitNetwork() == true ) //Inicjacja sieci
		{
			//chat -> AddLine(RakString("Establishing connection with %s:%s...", config->GetServerIp().C_String(), config->GetServerPort().C_String()), zCOLOR(68, 255, 0, 255));
			chat -> AddLine(RakString("Nawi�zywanie po��czenia z %s:%s...", config->GetServerIp().C_String(), config->GetServerPort().C_String()), zCOLOR(255, 196, 0, 255));
			//net -> Connect() przeniesione do pierwszej klatki rendera
		}	
	}
};