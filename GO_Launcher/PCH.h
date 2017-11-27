#ifndef __PCH__
#define __PCH__

#define WINVER 0x0500
#define _WIN32_WINNT 0x0500

// Defines
#include "Macros.h"
#include "GlobalDefines.h"
#include "ServerUnknow.h"
#include "SettingUnknow.h"

//#define DEBUG_MODE

// Debug mode
#ifdef DEBUG_MODE
#include <QDebug>
#endif

// Headers
#include "SLauncher.h"
#include "SLog.h"
#include "CLanguage.h"
#include "CServerInfo.h"
#include "CServerManager.h"
#include "CSettings.h"
#include "CAddons.h"
#include "COptions.h"
#include "CMessageBox.h"
#include "CFavorite.h"
#include "CInternetManager.h"
#include "CFavoriteManager.h"
#include "CNetwork.h"
#include "CNetworkThread.h"
#include "CFileTransferCallback.h"
#include "CDownloader.h"
#include "CUrlDownloader.h"
#include "CMasterServerList.h"
#include "CInject.h"
#include "CVersion.h"

// RPC
#include "RPC/CRPCInternet.h"
#include "RPC/CRPCFavorite.h"
#include "RPC/CRPCDownloader.h"

// UI
#include "ui_SLauncher.h"
#include "ui_CAddons.h"
#include "ui_COptions.h"
#include "ui_CMessageBox.h"
#include "ui_CFavorite.h"
#include "ui_CDownloader.h"
#include "ui_CUrlDownloader.h"

#endif // PCH

