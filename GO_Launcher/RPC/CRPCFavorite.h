#ifndef CRPC_FAVORITE_H
#define CRPC_FAVORITE_H

#include <QObject>
#include <QQueue>
#include <QTimer>

#include "RakNetInclude.h"

class CRPCFavorite : public QObject
{
    Q_OBJECT

signals:
    void signalFillUnknownServers();
    void signalServerInformation(QString ipAdress, QString port, QString hostName, QString script, QString version,
                                 QString world, QString description, int onlinePlayers, int maxPlayers, int ping);

public:
    CRPCFavorite();

    void handlePacket(RakNet::Packet *packet);
    void enableRefreshTimer(bool value);

    // RakNet messages
    void connectionFailed(RakNet::Packet *packet);
    void connectionRequest(RakNet::Packet *packet);
    void disconnected(RakNet::Packet *packet);
    void serverReached(RakNet::Packet *packet);

    // GO messages
    void serverInformation(RakNet::Packet *packet);

private:
    void initConnections();
    void getInformation();
    void finishGettingInformation();

    struct Server
    {
        QString m_IP;
        int     m_Port;

        Server() {}
        Server(QString ipAdress, int port) : m_IP(ipAdress), m_Port(port) {}
    };

    QQueue<Server> m_ServerQueue;
    QTimer m_TimerRefresh;
    bool m_CheckingServer;

private slots:
    void onTimerRefresh();
};

#endif // CRPC_H
