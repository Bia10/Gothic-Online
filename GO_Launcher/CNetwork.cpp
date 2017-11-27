#include "PCH.h"

CNetwork::CNetwork() :
    m_Peer(RakNet::RakPeerInterface::GetInstance()),
    m_ServerList(NULL),
    m_CurrServers(NULL),
    m_MaxServers(NULL),
    m_MsgBoxCheckingFiles(false),
    m_MsgBoxConnectionFailed(true)
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
    initConnections();
    NETWORK.start(m_Thread, m_Peer);

    RakNet::SocketDescriptor socketDescriptor;
    if (m_Peer->Startup(1, &socketDescriptor, 1) != RakNet::RAKNET_STARTED)
    {
        CMessageBox::warrning(TRANSLATE("N_NAME"), TRANSLATE("N_RAKNET_ERROR"));
    }
}

CNetwork::~CNetwork()
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
    NETWORK.setRunning(false);

    m_Thread.quit();
    m_Thread.wait();
    m_Thread.deleteLater();

    m_Peer->Shutdown(300);
    RakNet::RakPeerInterface::DestroyInstance(m_Peer);
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Public method
//-------------------------------------------------------------------------------------------------------------------------------

void CNetwork::sendRequest(QVector<CServerInfo> &serverList, int index)
{
    NETWORK.setIndex(index);

    m_CurrServers = 0; m_MaxServers = serverList.size();
    if (m_MaxServers > 0)
    {
        LAUNCHER.setStatus(QString(TRANSLATE("SB_CHECKING_SERVERS")).arg(m_CurrServers + 1).arg(m_MaxServers));

        // Thread safe
        m_Mutex.lock();
        for (CServerInfo &info : serverList)
            m_Peer->Ping(info.getIpAdress().toStdString().c_str(), info.getPort().toInt(), false);
        m_Mutex.unlock();

        if (index == INDEX_FAVORITE)
            NETWORK.getFavoriteRPC()->enableRefreshTimer(true);
    }
    else
        LAUNCHER.setStatus(TRANSLATE("SB_NO_SERVERS"));
}

void CNetwork::sendRequest(QString ipAdress, int port, int index)
{
    NETWORK.setIndex(index);
    // Thread safe
    m_Mutex.lock();
    m_Peer->Ping(ipAdress.toStdString().c_str(), port, false);
    m_Mutex.unlock();

    if (index == INDEX_FAVORITE)
        NETWORK.getFavoriteRPC()->enableRefreshTimer(true);
}

bool CNetwork::downloadServerFiles(QString hostName, QString ipAdress, int port)
{
    m_TempServerName = hostName;
    return NETWORK.connectToServer(ipAdress, port);
}

void CNetwork::downloadFileFromUrl(QString url, int index)
{
    m_DownloadIndex = index;
    m_UrlDownloader.downloadFile(url);
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Public slots
//-------------------------------------------------------------------------------------------------------------------------------

void CNetwork::onTabIndexChanged(int index)
{
    if (index == INDEX_INTERNET)
        NETWORK.getFavoriteRPC()->enableRefreshTimer(false);

    LAUNCHER.onRefresh();
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Private method
//-------------------------------------------------------------------------------------------------------------------------------

void CNetwork::initConnections()
{
    // Internet
    connect(NETWORK.getInternetRCP(), SIGNAL(signalServerPing(QString,int,int)),
            this, SLOT(onInternetServerReached(QString,int,int)));

    // Favorite
    connect(NETWORK.getFavoriteRPC(), SIGNAL(signalFillUnknownServers()),
            this, SLOT(onFavoriteFillUnknownServers()));

    connect(NETWORK.getFavoriteRPC(), SIGNAL(signalServerInformation(QString,QString,QString,QString,QString,QString,QString,int,int,int)),
            this, SLOT(onServerInformation(QString,QString,QString,QString,QString,QString,QString,int,int,int)));

    // Downloader
    connect(&NETWORK, SIGNAL(signalDownloaderQuit()),
            this, SLOT(onDownloaderQuit()));

    connect(NETWORK.getDownloaderRPC(), SIGNAL(signalConnectionFailed()),
            this, SLOT(onDownloaderConnectionFailed()));

    connect(NETWORK.getDownloaderRPC(), SIGNAL(signalCheckingFiles()),
            this, SLOT(onDownloaderCheckingFiles()));

    connect(NETWORK.getFileTransferCallback(), SIGNAL(onFileShow()),
            this, SLOT(onDownloaderShow()));

    connect(NETWORK.getFileTransferCallback(), SIGNAL(onFileNew(uint,uint,uint,uint,uint,uint,QString)),
            this, SLOT(onDownloaderNewFile(uint,uint,uint,uint,uint,uint,QString)));

    connect(NETWORK.getFileTransferCallback(), SIGNAL(onFileProgress(uint,uint,uint,uint)),
            this, SLOT(onDownloaderFileProgress(uint,uint,uint,uint)));

    connect(NETWORK.getFileTransferCallback(), SIGNAL(onFileSaved(uint,uint,QString)),
            this, SLOT(onDownloaderFileSaved(uint,uint,QString)));

    connect(NETWORK.getFileTransferCallback(), SIGNAL(onFileDownloadComplete()),
            this, SLOT(onDownloaderComplete()));

    // Url
    connect(&m_UrlDownloader, SIGNAL(signalDownloadCompleteCache(QString)),
            this, SLOT(onUrlDownloadComplete(QString)));

    connect(&m_UrlDownloader, SIGNAL(signalError()),
            this, SLOT(onUrlError()));
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Private slots
//-------------------------------------------------------------------------------------------------------------------------------

// Internet
void CNetwork::onInternetServerReached(QString ipAdress, int port, int ping)
{
    LAUNCHER.getInternetManager().addServer(ipAdress, port, ping);
}

// Favorite
void CNetwork::onFavoriteFillUnknownServers()
{
    m_CurrServers == 0 ? LAUNCHER.setStatus(TRANSLATE("SB_NO_SERVERS")) :
                         LAUNCHER.setStatus(QString(TRANSLATE("SB_AVAIABLE_SERVERS")).arg(m_CurrServers));

    LAUNCHER.getServerFavoriteManager()->showRestServers();
}

void CNetwork::onServerInformation(QString ipAdress, QString port, QString hostName, QString script, QString version,
                                   QString world, QString description, int onlinePlayers, int maxPlayers, int ping)
{
    LAUNCHER.setStatus(QString(TRANSLATE("SB_CHECKING_SERVERS")).arg(++m_CurrServers).arg(m_MaxServers));
    LAUNCHER.getServerFavoriteManager()->insertServer(ipAdress, port, hostName, description, script, world, version, onlinePlayers, maxPlayers, ping);
}

// Downloader
void CNetwork::onDownloaderQuit()
{
    LAUNCHER.enable();

    m_Downloader.onQuit();
}

void CNetwork::onDownloaderConnectionFailed()
{
    LAUNCHER.enable();

    m_MsgBoxConnectionFailed.setWindowTitle(m_TempServerName);
    m_MsgBoxConnectionFailed.setText(TRANSLATE("D_CONNECT_FAILED"));
    m_MsgBoxConnectionFailed.show();
}

void CNetwork::onDownloaderCheckingFiles()
{
    LAUNCHER.disable();

    m_MsgBoxCheckingFiles.setWindowTitle(m_TempServerName);
    m_MsgBoxCheckingFiles.setText(TRANSLATE("D_CHECKING_FILES"));
    m_MsgBoxCheckingFiles.show();
}

void CNetwork::onDownloaderShow()
{
    m_MsgBoxCheckingFiles.close();

    m_Downloader.setWindowTitle(m_TempServerName);
    m_Downloader.show();
}

void CNetwork::onDownloaderNewFile(unsigned partCount, unsigned partTotal, unsigned totalCount, unsigned totalSize, unsigned fileIndex, unsigned filesAmount, QString fileName)
{
    m_Downloader.setupFile(partCount, partTotal, totalCount, totalSize, fileIndex, filesAmount, fileName);
}

void CNetwork::onDownloaderFileProgress(unsigned partCount, unsigned partTotal, unsigned totalCount, unsigned totalSize)
{
    m_Downloader.updateFileProgress(partCount, partTotal, totalCount, totalSize);
}

void CNetwork::onDownloaderFileSaved(unsigned fileIndex, unsigned filesAmount, QString fileName)
{
    m_Downloader.saveFile(fileIndex, filesAmount, fileName);
}

void CNetwork::onDownloaderComplete()
{
    LAUNCHER.enable();

    NETWORK.disconnectFromCurrent();

    m_Downloader.close();
    m_MsgBoxCheckingFiles.close();

    int gothicProcessID = LAUNCHER.getInjector().RunApplication(INJECT_APP_NAME);
    if (gothicProcessID)
    {
        if (!LAUNCHER.getInjector().InjectDLL(gothicProcessID, INJECT_DLL_NAME))
            CMessageBox::warrning(APP_NAME, QString(TRANSLATE("IR_ERR_01")).arg(INJECT_DLL_NAME));
    }
    else
        CMessageBox::warrning(APP_NAME, QString(TRANSLATE("IR_ERR_02")).arg(INJECT_APP_NAME));
}

// Url Downloader
void CNetwork::onUrlDownloadComplete(QString param)
{
    switch (m_DownloadIndex)
    {
    case FILE_URL_MASTER_LIST:
        LAUNCHER.getInternetManager().splitList(param);
        break;

    case FILE_URL_VERSION:
        LAUNCHER.getVersionManager().updateVersionInfo(param);
        break;
    }
}

void CNetwork::onUrlError()
{
    switch (m_DownloadIndex)
    {
    case FILE_URL_MASTER_LIST:
        LAUNCHER.getInternetManager().downloadError();
        break;
    }

    m_DownloadIndex = -1; // Restart index
}
