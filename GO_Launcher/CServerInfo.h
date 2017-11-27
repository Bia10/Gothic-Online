#ifndef CSERVERINFO_H
#define CSERVERINFO_H

#include <QString>
#include <QTreeWidgetItem>

#include "ServerUnknow.h"

class CServerInfo
{
public:
    CServerInfo(QString ipAdress	  = ServerUnknow::IP_ADRESS,
                QString port 		  = ServerUnknow::PORT,
                QString hostName      = ServerUnknow::HOSTNAME,
                QString description   = ServerUnknow::DESCRIPTION,
                QString version       = ServerUnknow::VERSION,
                QString world         = ServerUnknow::WORLD,
                QString script        = ServerUnknow::SCRIPT,
                uint onlinePlayers 	  = ServerUnknow::ONLINE_PLAYERS,
                uint maxPlayers 	  = ServerUnknow::MAX_PLAYERS,
                uint ping		 	  = ServerUnknow::PING);

    inline QString  getHostName()      { return m_HostName; }
    inline QString  getIpAdress()      { return m_IpAdress; }
    inline QString  getPort()          { return m_Port; }
    inline QString  getDescription()   { return m_Description; }
    inline QString  getVersion()       { return m_Version; }
    inline QString  getWorld()         { return m_World; }
    inline QString  getScript()        { return m_Script; }
    inline uint 	getOnlinePlayers() { return m_OnlinePlayers; }
    inline uint 	getMaxPlayers()    { return m_MaxPlayers; }
    inline uint 	getPing()          { return m_Ping; }
    inline bool     exits()            { return m_Exist; }
    inline bool     isShowed()         { return m_IsShowed; }

private:
    QTreeWidgetItem *m_ptrItem;
    QString m_IpAdress, m_Port, m_HostName, m_Description, m_Version, m_World, m_Script;
    uint m_OnlinePlayers, m_MaxPlayers, m_Ping;
    bool m_IsShowed, m_Exist;

friend class CServerManager;
friend class CInternetManager;
friend class CFavoriteManager;
};

#endif // CSERVERINFO_H
