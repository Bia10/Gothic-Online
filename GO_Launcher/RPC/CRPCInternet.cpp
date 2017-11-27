#include "PCH.h"

void CRPCInternet::handlePacket(RakNet::Packet *packet)
{
    switch (packet->data[0])
    {
    // RakNet messages
    case ID_UNCONNECTED_PONG:
        serverReached(packet);
        break;
    }
}

void CRPCInternet::serverReached(RakNet::Packet *packet)
{
    RakNet::TimeMS time;

    RakNet::BitStream bsIn(packet->data, packet->length, false);
    bsIn.IgnoreBytes(1);
    bsIn.Read(time);

    emit signalServerPing(packet->systemAddress.ToString(false), packet->systemAddress.GetPort(), RakNet::GetTime() - time);
}
