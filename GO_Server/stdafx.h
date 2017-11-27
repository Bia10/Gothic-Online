// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#define _CRT_SECURE_NO_WARNINGS
//#define DEBUG_MODE

#include <iostream>
#include <map>
#include <queue>
#include <fstream>
using namespace std;

//Defines
//#define DEV_MODE
#define BAN_LIST RakString("banlist")
#define versionString "0.4.6a"

#include "Log/Log.h"

//Gothic Online headers
#include "../Shared/GO_SharedIncludes.h"
#include "../Shared/hashlib/hashlibpp.h"
//Managery
#include "CPlayerManager.h"
#include "CItemManager.h"
#include "CBotManager.h"
//Headery samego multiplayera
#include "CMaster.h" //Master server
#include "CMultiplayer.h"
#include "CConfig.h"
#include "CReceiver.h"
#include "CNetwork.h"
#include "CNetworkError.h"
#include "CScriptDownload.h"
#include "CStreamer.h"
#include "CAdmin.h"
#include "CBan.h"
#include "CServer.h" //G³ówny header serwera
//obiekty
#include "CCreature.h"
#include "CNpc.h"
#include "CPlayer.h"
#include "CItem.h"
//RPC
#include "RPC/ConnectionRPC.h"
#include "RPC/ChatRPC.h"
#include "RPC/PlayerRPC.h"
#include "RPC/ItemRPC.h"
#include "RPC/LauncherRPC.h"
#include "RPC/ScriptRPC.h"
//Skrypty
#include "Script/SVariable.h"
#include "Script/STimer.h"
#include "Script/SCallback.h"
#include "Script/SFunction.h"
#include "Script/CScript.h"
