#ifndef CNETWORK_H
#define CNETWORK_H

#include <QObject>
#include <QThread>

#include "RakNetInclude.h"
#include "CNetworkThread.h"
#include "CServerInfo.h"
#include "CDownloader.h"
#include "CUrlDownloader.h"
#include "CMessageBox.h"

class CServerManager;

class CNetwork : public QObject
{
    Q_OBJECT

public:
    CNetwork();
    ~CNetwork();

    void sendRequest(QVector<CServerInfo> &serverList, int index);
    void sendRequest(QString ipAdress, int port, int index);
    bool downloadServerFiles(QString hostName, QString ipAdress, int port);
    void downloadFileFromUrl(QString url, int index = 0);

public slots:
    void onTabIndexChanged(int index);

private:
    void initConnections();
    void connectServer();

    RakNet::RakPeerInterface *m_Peer;

    QThread m_Thread;
    QMutex m_Mutex;
    QVector<CServerInfo> m_ServerList;
    CServerManager *m_ServerManager;

    CDownloader m_Downloader;
    CUrlDownloader m_UrlDownloader;
    CMessageBox m_MsgBoxConnectionFailed, m_MsgBoxCheckingFiles;
    QString m_TempServerName;

    int m_CurrServers, m_MaxServers, m_DownloadIndex;

private slots:
    // Internet
    void onInternetServerReached(QString ipAdress, int port, int ping);

    // Favorite slots
    void onFavoriteFillUnknownServers();
    void onServerInformation(QString ipAdress, QString port, QString hostName, QString script, QString version,
                             QString world, QString description, int onlinePlayers, int maxPlayers, int ping);
    // Downloader slots
    void onDownloaderQuit();
    void onDownloaderConnectionFailed();
    void onDownloaderCheckingFiles();
    void onDownloaderShow();
    void onDownloaderNewFile(unsigned partCount, unsigned partTotal, unsigned totalCount, unsigned totalSize, unsigned fileIndex, unsigned filesAmount, QString fileName);
    void onDownloaderFileProgress(unsigned partCount, unsigned partTotal, unsigned totalCount, unsigned totalSize);
    void onDownloaderFileSaved(unsigned fileIndex, unsigned filesAmount, QString fileName);
    void onDownloaderComplete();

    // Url slots
    void onUrlDownloadComplete(QString param);
    void onUrlError();
};

#endif // CNETWORK_H
