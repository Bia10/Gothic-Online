#ifndef RAKNETINCLUDE
#define RAKNETINCLUDE

#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <BitStream.h>
#include <RakSleep.h>
#include <GetTime.h>

#define RAKMSG(x) static_cast<RakNet::MessageID>(x)
#define RAKMSG_SIZE sizeof(RakNet::MessageID)

// Messages ID
enum EGOMessage
{
    GO_LAUNCHER = 135,
};

#endif // RAKNETINCLUDE

