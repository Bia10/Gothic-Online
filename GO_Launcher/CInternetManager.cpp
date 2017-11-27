#include "PCH.h"

CInternetManager::CInternetManager() :
    m_MasterServerList(LAUNCHER.cryptString(MASTERSERVER_LINK_LENGHT, MASTERSERVER_LINK).c_str()),
    m_MsgBoxMasterServer(false),
    m_MsgBoxConnectionFailed(true),
    m_MasterServer(m_SplitThread)
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
    initConnections();
}

CInternetManager::~CInternetManager()
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
    clear();
    m_SplitThread.deleteLater();
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Public method
//-------------------------------------------------------------------------------------------------------------------------------

void CInternetManager::translate()
{
    m_MsgBoxMasterServer.setWindowTitle("");
    m_MsgBoxMasterServer.setText(TRANSLATE("I_MASTER_LIST"));

    m_MsgBoxConnectionFailed.setWindowTitle("");
    m_MsgBoxConnectionFailed.setText(TRANSLATE("I_MASTER_ERROR"));
}

void CInternetManager::serverList()
{
    clear();

    LAUNCHER.disable();

    LAUNCHER.getServerInternetManager()->clear();
    LAUNCHER.getNetwork().downloadFileFromUrl(LAUNCHER.decryptString(m_MasterServerList.toStdString()).c_str());
    LAUNCHER.setStatus(TRANSLATE("I_MASTER_CONNECTING"));

    m_MsgBoxMasterServer.show();
}

void CInternetManager::clear()
{
    if (m_SplitThread.isRunning())
    {
        m_MasterServer.threadStop();

        m_SplitThread.quit();
        m_SplitThread.wait();

        m_MasterServer.threadRenew();
    }
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Private method
//-------------------------------------------------------------------------------------------------------------------------------

void CInternetManager::initConnections()
{
    connect(&m_MasterServer, SIGNAL(signalAddServer(CServerInfo)),
            this, SLOT(onShowServer(CServerInfo)));
}

void CInternetManager::splitList(QString list)
{
    m_ServerList.clear();
    m_MasterServer.setListData(list);
    m_SplitThread.start();
    m_MsgBoxMasterServer.close();

    LAUNCHER.setStatus(TRANSLATE("SB_NO_SERVERS"));
    LAUNCHER.enable();
}

void CInternetManager::downloadError()
{
    LAUNCHER.enable();

    m_MsgBoxMasterServer.close();
    m_MsgBoxConnectionFailed.show();
}

void CInternetManager::addServer(QString ipAdress, int port, int ping)
{
    QString mapIndex = ipAdress + ":" + TOSTRING(port);
    if (!m_ServerList.contains(mapIndex)) return;

    m_ServerList[mapIndex].m_Ping = ping;

    LAUNCHER.getServerInternetManager()->addServer(m_ServerList[mapIndex]);
    LAUNCHER.setStatus(QString(TRANSLATE("SB_AVAIABLE_SERVERS")).arg(LAUNCHER.getServerInternetManager()->getServerList().size()));
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Private slots
//-------------------------------------------------------------------------------------------------------------------------------

void CInternetManager::onShowServer(CServerInfo serverInfo)
{
    QString mapIndex = serverInfo.getIpAdress() + ":" + serverInfo.getPort();
    m_ServerList[mapIndex] = serverInfo;

    LAUNCHER.getNetwork().sendRequest(serverInfo.getIpAdress(), serverInfo.getPort().toInt(), INDEX_INTERNET);
}
