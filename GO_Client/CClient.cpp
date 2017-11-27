#include "stdafx.h"


CClient::CClient()
{
	new MemLib();
	new CLog();

	DLOG("Gothic Online Debug Console Initialized!");
	DLOG("CClient::CClient()");

	bIsLateHooksInitiated = false;

	pSplashScreen = new CSplashScreen();
	pGothicGame = new CGothicGame();
	pRender = new CRender();
	pConfig = new CConfig();
	pNetwork = new CNetwork();
	pMultiplayer = new CMultiplayer();
	pChat = new CChat();
	pKeyBoard = new CKeyBoard();
};

CClient::~CClient()
{
	DLOG("CClient::~CClient()");
	this->DeInitializeHooks();
	if( IsLateHooksInitiated() == true )
		this->DeInitializeLateHooks();

	delete pMemLib;
	delete pSplashScreen;
	delete pGothicGame;
	delete pRender;
	delete pConfig;
	delete pNetwork;
	delete pMultiplayer;
	delete pChat;
	delete pKeyBoard;
};

void CClient::Start()
{
	DLOG("CClient::Start()");
	//Zmiana nazwy okna
	//CGothicWindow::SetGothicWindowName(RakString("Gothic Online"));
	//Wstawianie hook'ów
	this->InitializeHooks();

	// Initialize keyboard layout
	if (pConfig->GetLanguage() == "ru")
		pKeyBoard->SetLayout(CKeyBoard::RUSSIAN);

	DLOG("Client started");
};

void CClient::ApplyPatches()
{
	DLOG("CClient::ApplyPatches()");

};

void CClient::InitializeHooks()
{
	DLOG("CClient::InitializeHooks()");
	pMemLib->ImportHook(0x00429B80, sizeof(int(CGameManager::*)(zSTRING,int)), &CGameManager::Fake_PlayVideo); //Filmiki na pocz¹tku gry
	pMemLib->ImportHook(0x0042A310, sizeof(int(*)()), &Hook_Apply_Options_Video); //Zmiana rozdzielczosci
	pMemLib->ImportHook(0x004279F0, sizeof(void(CGameManager::*)(int)), &CGameManager::Hook_Menu); //Hook na menu, "odczepia" siê w innym miejscu
	pMemLib->ImportHook(0x0045D080, sizeof(zSTRING(zCOption::*)(const zSTRING&, const char*, const char*)), &zCOption::Hook_ReadString); //Tutaj zablokujê opcjê "NOWA GRA" z menu
	pMemLib->ImportHook(0x0063CD60, sizeof(void(oCGame::*)(const zSTRING&, const zSTRING&)), &oCGame::Hook_ChangeLevel); //Zmiana mapy
	pMemLib->ImportHook(0x0063EAD0, sizeof(void(oCGame::*)(oCNpc*,int,const zSTRING&)), &oCGame::Hook_EnterWorld); //Wejscie do swiata
	pMemLib->ImportHook(0x0063AD80, sizeof(void(oCGame::*)(int,int)), &oCGame::Fake_WriteSavegame); //Blokowanie zapisywania gry
	pMemLib->ImportHook(0x0063C2A0, sizeof(void(oCGame::*)(int,int)), &oCGame::Fake_LoadSavegame); //Blokowanie wczytywania gry (bo crash)
	pMemLib->ImportHook(0x00424850, sizeof(void(CGameManager::*)(void)), &CGameManager::Hook_Done); //Zamykanie gry
#ifndef DEV_MODE
	pMemLib->ImportHook(0x4301F0, sizeof(void(*)(zSTRING)), &Fake_HandleResultString); //Czity gothicowe (marvin, southpark etc.)
#endif //DEV_MODE
};

void CClient::DeInitializeHooks()
{
	DLOG("CClient::DeInitializeHooks()");
	pMemLib->RemoveHook(0x00429B80); //filmiki na pocz¹tku
	pMemLib->RemoveHook(0x0042A310); //Zmiana rozdzielczosci
	pMemLib->RemoveHook(0x0045D080); //NOWA GRA z menu
	pMemLib->RemoveHook(0x0063CD60); //Zmiana mapy
	pMemLib->RemoveHook(0x0063EAD0); //Wejscie do swiata
	pMemLib->RemoveHook(0x0063AD80); //Zapis gry
	pMemLib->RemoveHook(0x0063C2A0); //Wczytanie gry
	pMemLib->RemoveHook(0x00424850); //Zamykanie gry

#ifndef DEV_MODE
	pMemLib->RemoveHook(0x4301F0); //Gothicowe czity
#endif //DEV_MODE
};

void CClient::InitializeLateHooks()
{
	DLOG("CClient::InitializeLateHooks()");
	pMemLib->ImportHook(0x0063DBE0, sizeof(void(oCGame::*)(void)), &oCGame::Hook_Render); //Render
	pMemLib->ImportHook(0x0065EEE0, sizeof(int(oCGame::*)(int)), &oCGame::Hook_HandleEvent); //Hook na klawiaturê
	//pMemLib->ImportHook(0x005612F0, sizeof(void(zCModel::*)(zCModelAni*,int)), &zCModel::Hook_StartAni); //Animacje
	pMemLib->ImportHook(0x00694230, sizeof(void(oCNpc::*)(void)), &oCNpc::Fake_DropAllInHand); //Blokowanie wypadania miecza przy upadku
	pMemLib->ImportHook(0x0046FC00, sizeof(void(oCMag_Book::*)(void)), &oCMag_Book::Hook_Spell_Cast); //Magia
	pMemLib->ImportHook(0x006A10F0, sizeof(int(oCNpc::*)(zCVob*)), &oCNpc::Hook_DoDropVob); //Wyrzucanie itemu
	pMemLib->ImportHook(0x006A0D10, sizeof(int(oCNpc::*)(zCVob*)), &oCNpc::Hook_DoTakeVob); //Podnoszenie itemu
	pMemLib->ImportHook(0x00694C50, sizeof(void(oCNpc::*)(int)), &oCNpc::Hook_SetMovLock); //Blokada ruchu (do skryptow)
	pMemLib->ImportHook(0x006BB0A0, sizeof(void(oCNpc::*)(void)), &oCNpc::Hook_OpenInventory); //OpenInventory
	pMemLib->ImportHook(0x006BB2F0, sizeof(void(oCNpc::*)(void)), &oCNpc::Hook_CloseInventory); //CloseInventory co tu du¿o mówiæ?
	pMemLib->ImportHook(0x0068AD40, sizeof(int(oCNpc::*)(zSTRING&)), &oCNpc::Hook_ApplyOverlay); // Przechwytywanie dodania overlay
	pMemLib->ImportHook(0x0068B040, sizeof(void(oCNpc::*)(zSTRING&)), &oCNpc::Hook_RemoveOverlay); // Przechwytywanie usuniêcia overlay
	pMemLib->ImportHook(0x006B0C60, sizeof(int(oCNpc::*)(zSTRING&, float)), &oCNpc::Hook_ApplyTimedOverlayMds);
	pMemLib->ImportHook(0x0067D300, sizeof(void(oCMobInter::*)(zCVob*, zCVob*)), &oCMobInter::Hook_OnTrigger);
	pMemLib->ImportHook(0x0067D5F0, sizeof(void(oCMobInter::*)(zCVob*, zCVob*)), &oCMobInter::Hook_OnUntrigger);
	pMemLib->ImportHook(0x006FFEB0, sizeof(void(zCView::*)(zINT, zINT, zSTRING &)), &zCView::Hook_Print);
	pMemLib->ImportHook(0x00692C10, sizeof(void(oCNpc::*)(float, oCNpc*)), &oCNpc::Hook_DropUnconscious);
	pMemLib->ImportHook(0x006A09F0, sizeof(void(oCNpc::*)(int)), &oCNpc::Hook_DoShootArrow);
	pMemLib->ImportHook(0x00741990, sizeof(void(oCNpc::*)(oSDamageDescriptor&)), &oCNpc::Hook_OnDamage_Anim);
	pMemLib->ImportHook(0x00738E40, sizeof(void(oCNpc::*)(oSDamageDescriptor&)), &oCNpc::Hook_OnDamage_Script);
	this->bIsLateHooksInitiated = true;
};

void CClient::DeInitializeLateHooks()
{
	DLOG("CClient::DeInitializeLateHooks()");
	pMemLib->RemoveHook(0x0063DBE0); //render
	pMemLib->RemoveHook(0x0065EEE0); //Hook na klawiaturê
	//pMemLib->RemoveHook(0x005612F0); //Animacje
	pMemLib->RemoveHook(0x00694230); //Blokowanie wypadania miecza przy upadku
	pMemLib->RemoveHook(0x0046FC00); //Magia
	pMemLib->RemoveHook(0x006A10F0); //Wyrzucenie itemu
	pMemLib->RemoveHook(0x006A0D10); //Podnoszenie itemu
	pMemLib->RemoveHook(0x00694C50); //Blokada ruchu
	pMemLib->RemoveHook(0x006BB0A0); //OpenInventory
	pMemLib->RemoveHook(0x006BB2F0); //CloseInventory
	pMemLib->RemoveHook(0x0068AD40); //Przechwytywanie dodania overlay
	pMemLib->RemoveHook(0x0068B040); //Przechwytywanie usuniêcia overlay
	pMemLib->RemoveHook(0x006B0C60);
	pMemLib->RemoveHook(0x0067D300);
	pMemLib->RemoveHook(0x0067D5F0);
	pMemLib->RemoveHook(0x006FFEB0);
	pMemLib->RemoveHook(0x00692C10);
	pMemLib->RemoveHook(0x006A09F0);
	pMemLib->RemoveHook(0x00741990);
	pMemLib->RemoveHook(0x00738E40);
	this->bIsLateHooksInitiated = false;
};