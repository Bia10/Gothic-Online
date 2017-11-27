#include "PCH.h"

CNetworkThread::CNetworkThread() :
    m_ThreadRunning(true),
    m_EnableTCP(true),
    m_Unfinished(false),
    m_ServerPassword(LAUNCHER.cryptString(RAKNET_PASSWORD_LENGHT, RAKNET_PASSWORD))
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
}

CNetworkThread::~CNetworkThread()
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Public method
//-------------------------------------------------------------------------------------------------------------------------------

void CNetworkThread::start(QThread &thread, RakNet::RakPeerInterface *peer)
{
    m_ptrPeer = peer;

    m_RakTCP.Start(65432, 1);
    initConnections(thread);
    moveToThread(&thread);

    thread.start();
}

void CNetworkThread::setRunning(bool value)
{
    m_ThreadRunning = value;
}

bool CNetworkThread::connectToServer(QString ipAdress, int port)
{
    if (m_EnableTCP) m_RakTCP.Connect(ipAdress.toStdString().c_str(), port);
    return m_EnableTCP;
}

void CNetworkThread::disconnectFromCurrent(bool unfinished)
{
    // Simply TCP receiver blocking (anti-crash)
    m_EnableTCP = false; m_Unfinished = unfinished;
}

void CNetworkThread::setIndex(int index)
{
    m_Index = index;
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Private method
//-------------------------------------------------------------------------------------------------------------------------------

CNetworkThread& CNetworkThread::getInstance()
{
    static CNetworkThread instance;
    return instance;
}

void CNetworkThread::initConnections(QThread &thread)
{
    connect(&thread, SIGNAL(started()),
            this, SLOT(handleNetwork()));

    connect(&thread, SIGNAL(finished()),
            &thread, SLOT(deleteLater()));
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Private slots
//-------------------------------------------------------------------------------------------------------------------------------

void CNetworkThread::handleNetwork()
{
    while (m_ThreadRunning)
    {
        for (m_Packet = m_ptrPeer->Receive(); m_Packet; m_ptrPeer->DeallocatePacket(m_Packet), m_Packet = m_ptrPeer->Receive())
            switch (m_Index)
            {
            case INDEX_INTERNET:
                m_InternetRPC.handlePacket(m_Packet);
                break;

            case INDEX_FAVORITE:

                m_FavoriteRPC.handlePacket(m_Packet);
                break;
            }

        // Only this way work with all file size in downloader, otherwise program crash!
        if (m_EnableTCP)
            for (m_Packet = m_RakTCP.Receive(); m_Packet; m_RakTCP.DeallocatePacket(m_Packet), m_Packet = m_RakTCP.Receive());
        else
        {
            // Clear downloader
            m_DownloaderRPC.cancelDownload(m_Unfinished);
            m_RakTCP.CloseConnection(m_serverAdress);

            m_EnableTCP = true;

            emit signalDownloaderQuit();
        }

        m_DownloaderRPC.handle();

        RakSleep(10);
    }
}
