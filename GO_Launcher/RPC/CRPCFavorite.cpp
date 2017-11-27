#include "PCH.h"

CRPCFavorite::CRPCFavorite() :
    m_CheckingServer(false)
{
    initConnections();
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Public method
//-------------------------------------------------------------------------------------------------------------------------------

void CRPCFavorite::handlePacket(RakNet::Packet *packet)
{
    switch (packet->data[0])
    {
    // RakNet messages
    case ID_CONNECTION_ATTEMPT_FAILED:
        connectionFailed(packet);
        break;

    case ID_CONNECTION_REQUEST_ACCEPTED:
        connectionRequest(packet);
        break;

    case ID_DISCONNECTION_NOTIFICATION:
    case ID_CONNECTION_LOST:
        disconnected(packet);
        break;

    case ID_UNCONNECTED_PONG:
        serverReached(packet);
        break;

    // GO messages
    case GO_LAUNCHER:
        serverInformation(packet);
        break;
    }
}

void CRPCFavorite::enableRefreshTimer(bool value)
{
    value ? m_TimerRefresh.start(LIST_TIMEOUT) : m_TimerRefresh.stop(), m_ServerQueue.clear();
}

//-------------------------------------------------------------------------------------------------------------------------------

void CRPCFavorite::connectionFailed(RakNet::Packet *packet)
{
    Q_UNUSED(packet)
    finishGettingInformation();
}

void CRPCFavorite::connectionRequest(RakNet::Packet *packet)
{
    RakNet::BitStream bsIn;
    bsIn.Write(RAKMSG(GO_LAUNCHER));

    NETWORK.m_ptrPeer->Send(&bsIn, HIGH_PRIORITY, RELIABLE, NULL, packet->systemAddress, false);
}

void CRPCFavorite::disconnected(RakNet::Packet *packet)
{
    Q_UNUSED(packet)
    finishGettingInformation();
}

void CRPCFavorite::serverReached(RakNet::Packet *packet)
{
    m_ServerQueue.enqueue(Server(packet->systemAddress.ToString(false), packet->systemAddress.GetPort()));
    getInformation();
}

void CRPCFavorite::serverInformation(RakNet::Packet *packet)
{
    QString ipAdress = packet->systemAddress.ToString(false), port = TOSTRING(packet->systemAddress.GetPort());
    RakNet::RakString hostName, script, version, world, description, maxPlayers;
    uint onlinePlayers, maxPlayersConverted;

    RakNet::BitStream bsOut(packet->data, packet->length, false);
    bsOut.IgnoreBytes(RAKMSG_SIZE);
    bsOut.Read(hostName);
    bsOut.Read(onlinePlayers);
    bsOut.Read(maxPlayers);
    bsOut.Read(description);
    bsOut.Read(script);
    bsOut.Read(version);
    bsOut.Read(world);

    maxPlayersConverted = QString(maxPlayers.C_String()).toInt();

    NETWORK.m_ptrPeer->CloseConnection(packet->systemAddress, true);

    emit signalServerInformation(ipAdress, port, QString(hostName.C_String()), QString(script.C_String()), QString(version.C_String()), QString(world.C_String()),
                                 QString(description.C_String()), onlinePlayers, maxPlayersConverted, NETWORK.m_ptrPeer->GetLastPing(packet->systemAddress));
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Private method
//-------------------------------------------------------------------------------------------------------------------------------

void CRPCFavorite::initConnections()
{
    connect(&m_TimerRefresh, SIGNAL(timeout()),
            this, SLOT(onTimerRefresh()));
}

void CRPCFavorite::getInformation()
{
    if (!m_CheckingServer && m_ServerQueue.size() > 0)
    {
        m_CheckingServer = true;
        std::string decryptedPassword = LAUNCHER.decryptString(NETWORK.m_ServerPassword);

        Server &server = m_ServerQueue.dequeue();
        NETWORK.m_ptrPeer->Connect(server.m_IP.toStdString().c_str(), server.m_Port,
                                   decryptedPassword.c_str(), decryptedPassword.length());
    }
}

void CRPCFavorite::finishGettingInformation()
{
    m_CheckingServer = false;
    getInformation();
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Private slots
//-------------------------------------------------------------------------------------------------------------------------------

void CRPCFavorite::onTimerRefresh()
{
    if (m_ServerQueue.isEmpty() && !m_CheckingServer)
    {
        m_TimerRefresh.stop();
        emit signalFillUnknownServers();
    }
}
