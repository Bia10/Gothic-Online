#ifndef CRPCINTERNET_H
#define CRPCINTERNET_H

#include <QObject>

#include "RakNetInclude.h"

class CRPCInternet : public QObject
{
    Q_OBJECT

signals:
    void signalServerPing(QString ipAdress, int port, int ping);

public:
    void handlePacket(RakNet::Packet *packet);

    // RakNet messages
    void serverReached(RakNet::Packet *packet);
};

#endif // CRPCINTERNET_H
