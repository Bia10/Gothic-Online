// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <map>
#include <vector>
#include <queue>

using namespace std;

//Gothic Online definicja dewelopera
//#define DEV_MODE
#define COOP
#define versionString "v0.4.6a"
#define PING_SYNC_LIMIT 800

//Gothic Online headers
#include "zengin\\ZenginIncludes.h" //ZenGin (silnik gothica)
#include "..\\..\\Shared\\GO_SharedIncludes.h" //RakNet, TinyXML, goMath
#include "..\\..\\Shared\\hashlib\hashlibpp.h"
#include "MemLib\\MemLib.h" //MemLib
#include "Log\\CLog.h" //Logi
//Externy
extern MemLib* pMemLib;
extern CLog* pLog;
//Splash screen
#include "CSplashScreen.h"
//Managery
#include "CPlayerManager.h"
#include "CItemManager.h"
#include "CVobManager.h"
//Headery samego multiplayera
#include "CSpell.h"
#include "CAnimation.h"
#include "CMultiplayer.h"
#include "CReceiver.h"
#include "CNetwork.h"
#include "CConfig.h"
#include "CGothicWindow.h"
#include "CGothicGame.h"
#include "CRender.h"
#include "CChat.h"
#include "CKeyboard.h"
#include "CClient.h" //G³ówny header clienta
//Obiekty
#include "CCreature.h"
#include "CNpc.h"
#include "CPlayer.h"
#include "CItem.h"
#include "CVob.h"
//Local player
#include "CLocalPlayer.h"
//RPC
#include "RPC\\ConnectionRPC.h"
#include "RPC\\ChatRPC.h"
#include "RPC\\PlayerRPC.h"
#include "RPC\\ItemRPC.h"
#include "RPC\\ScriptRPC.h"
//Interfejsy
#include "Interface\\CNetInterface.h"
#include "Interface\\COptionsMenu.h"
#include "Interface\\CPlayerList.h"
//Skrypty
#include "Script\\SAnticheat.h"
#include "Script\\SDraw.h"
#include "Script\\STexture.h"
#include "Script\\SVariable.h"
#include "Script\\STimer.h"
#include "Script\\SCallback.h"
#include "Script\\SFunction.h"
#include "Script\\SScript.h"
#include "Script\\SKey.h"
#include "Script\\CScript.h"
