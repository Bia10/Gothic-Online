#include "PCH.h"

CServerInfo::CServerInfo(QString ipAdress, QString port, QString hostName, QString description, QString version,
                         QString world, QString script, uint onlinePlayers, uint maxPlayers, uint ping) :
    m_ptrItem(NULL),
    m_IpAdress(ipAdress),
    m_Port(port),
    m_HostName(hostName),
    m_Description(description),
    m_Version(version),
    m_World(world),
    m_Script(script),
    m_OnlinePlayers(onlinePlayers),
    m_MaxPlayers(maxPlayers),
    m_Ping(ping),
    m_IsShowed(false),
    m_Exist(false)
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
}
