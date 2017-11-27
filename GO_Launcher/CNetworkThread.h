#ifndef CNETWORKTHREAD_H
#define CNETWORKTHREAD_H

#include <QObject>
#include <QThread>

#include <PacketizedTCP.h>

#include "RPC/CRPCInternet.h"
#include "RPC/CRPCFavorite.h"
#include "RPC/CRPCDownloader.h"

#include "RakNetInclude.h"

#define NETWORK CNetworkThread::getInstance()

class CNetworkThread : public QObject
{
    Q_OBJECT

signals:
    void signalDownloaderQuit();

public:
    ~CNetworkThread();

    inline CRPCInternet*          getInternetRCP()          { return &m_InternetRPC; }
    inline CRPCFavorite*          getFavoriteRPC()          { return &m_FavoriteRPC; }
    inline CRPCDownloader*        getDownloaderRPC()        { return &m_DownloaderRPC; }
    inline CFileTransferCallback* getFileTransferCallback() { return &m_FileTransferCallback; }

    void start(QThread &thread, RakNet::RakPeerInterface *peer);
    void setRunning(bool value);
    bool connectToServer(QString ipAdress, int port);
    void disconnectFromCurrent(bool unfinished = false);
    void setIndex(int index);

private:
    CNetworkThread();

    static CNetworkThread& getInstance();

    void initConnections(QThread &thread);

    std::string m_ServerPassword;
    RakNet::RakPeerInterface *m_ptrPeer;
    RakNet::PacketizedTCP m_RakTCP;
    RakNet::SystemAddress m_serverAdress;
    RakNet::Packet *m_Packet;
    CRPCInternet m_InternetRPC;
    CRPCFavorite m_FavoriteRPC;
    CRPCDownloader m_DownloaderRPC;
    CFileTransferCallback m_FileTransferCallback;
    bool m_ThreadRunning, m_EnableTCP, m_Unfinished;
    int m_Index;

private slots:
    void handleNetwork();

friend class CRPCFavorite;
friend class CRPCDownloader;
friend class CFileTransferCallback;
friend class CNetwork;
friend class CDownloader;
};

#endif // CNETWORKTHREAD_H
