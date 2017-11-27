#include <QFile>

#include "PCH.h"

CServerManager::CServerManager(QTreeWidget *treeWidget) :
    QObject(),
    m_TreeWidget(treeWidget),
    m_SortFilter(SORT_NONE),
    m_SortHostname(false),
    m_SortPlayers(false)
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
    initConnections();
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Public method
//-------------------------------------------------------------------------------------------------------------------------------

void CServerManager::fillServerInfo()
{
    LAUNCHER.getUI()->labelDescription->setText(TRANSLATE("SM_DESCRIPTION"));

    LAUNCHER.getUI()->viewHostname->setText(TRANSLATE("SM_HOSTNAME") + ServerUnknow::HOSTNAME);
    LAUNCHER.getUI()->viewIP->setText(TRANSLATE("SM_IP") + ServerUnknow::IP_ADRESS);
    LAUNCHER.getUI()->viewPort->setText(TRANSLATE("SM_PORT") + ServerUnknow::PORT);
    LAUNCHER.getUI()->viewWorld->setText(TRANSLATE("SM_WORLD") + ServerUnknow::WORLD);
    LAUNCHER.getUI()->viewVersion->setText(TRANSLATE("SM_VERSION") + ServerUnknow::VERSION);
    LAUNCHER.getUI()->viewOnlinePlayers->setText(TRANSLATE("SM_PLAYERS") + TOSTRING(ServerUnknow::ONLINE_PLAYERS) + "/" + TOSTRING(ServerUnknow::MAX_PLAYERS));
    LAUNCHER.getUI()->viewPing->setText(TRANSLATE("SM_PING") + TOSTRING(ServerUnknow::PING));
    LAUNCHER.getUI()->viewDescription->setText(ServerUnknow::DESCRIPTION);
}

CServerInfo& CServerManager::getServerInfo(QString ipAdress, QString port)
{
    for (CServerInfo &info : m_ServerList)
        if (info.getIpAdress() == ipAdress && info.getPort() == port)
            return info;

    // Exception, must be deleted manually
    CServerInfo *info = new CServerInfo;
    return *info;
}

void CServerManager::addServer(CServerInfo &serverInfo, bool show)
{
    CServerInfo& info = getServerInfo(serverInfo.getIpAdress(), serverInfo.getPort());

    if (!info.exits())
    {
        delete &info;

        if (show)
        {
            QTreeWidgetItem *itemServer = new QTreeWidgetItem;
            itemServer->setText(0, serverInfo.getHostName());
            itemServer->setText(1, serverInfo.getIpAdress());
            itemServer->setText(2, serverInfo.getPort());
            itemServer->setText(3, serverInfo.getVersion());
            itemServer->setText(4, TOSTRING(serverInfo.getOnlinePlayers()) + "/" + TOSTRING(serverInfo.getMaxPlayers()));
            itemServer->setText(5, TOSTRING(serverInfo.getPing()));

            m_TreeWidget->addTopLevelItem(itemServer);
            serverInfo.m_ptrItem = itemServer;
        }

        serverInfo.m_Exist = true;
        serverInfo.m_IsShowed = show;
        m_ServerList.append(serverInfo);
    }
}

void CServerManager::removeServer(QString ipAdress, QString port)
{
    for (int i = 0; i < m_ServerList.size(); ++i)
        if (m_ServerList[i].getIpAdress() == ipAdress && m_ServerList[i].getPort() == port)
        {
            delete m_ServerList.at(i).m_ptrItem;
            m_ServerList.remove(i);

            return;
        }
}

void CServerManager::editServer(QString ipAdress, QString port, QString newIpAdress, QString newPort)
{
    for (int i = 0; i < m_ServerList.size(); ++i)
        if (m_ServerList[i].getIpAdress() == ipAdress && m_ServerList[i].getPort() == port)
        {
            m_ServerList[i].m_IpAdress = newIpAdress;
            m_ServerList[i].m_Port = newPort;

            m_ServerList.at(i).m_ptrItem->setText(1, newIpAdress);
            m_ServerList.at(i).m_ptrItem->setText(2, newPort);

            return;
        }
}

void CServerManager::insertServer(QString ipAdress, QString port, QString hostName, QString descripion, QString script, QString world, QString version,
                                  int onlinePlayers, int maxPlayers, int ping)
{
    CServerInfo &info = getServerInfo(ipAdress, port);

    if (info.exits())
    {
        info.m_HostName = hostName;
        info.m_Description = descripion;
        info.m_Script = script;
        info.m_World = world;
        info.m_Version = version;
        info.m_OnlinePlayers = onlinePlayers;
        info.m_MaxPlayers = maxPlayers;
        info.m_Ping = ping;

        QTreeWidgetItem *itemServer = new QTreeWidgetItem;
        itemServer->setText(0, info.getHostName());
        itemServer->setText(1, info.getIpAdress());
        itemServer->setText(2, info.getPort());
        itemServer->setText(3, info.getVersion());
        itemServer->setText(4, TOSTRING(info.getOnlinePlayers()) + "/" + TOSTRING(info.getMaxPlayers()));
        itemServer->setText(5, TOSTRING(info.getPing()));

        m_TreeWidget->addTopLevelItem(itemServer);
        info.m_ptrItem = itemServer;
        info.m_IsShowed = true;

        m_TreeWidget->addTopLevelItem(info.m_ptrItem);
    }
    else
        delete &info;
}

void CServerManager::insertServer(QString ipAdress, QString port)
{
    CServerInfo &info = getServerInfo(ipAdress, port);

    if (info.exits())
    {
        QTreeWidgetItem *itemServer = new QTreeWidgetItem;
        itemServer->setText(0, info.getHostName());
        itemServer->setText(1, info.getIpAdress());
        itemServer->setText(2, info.getPort());
        itemServer->setText(3, info.getVersion());
        itemServer->setText(4, TOSTRING(info.getOnlinePlayers()) + "/" + TOSTRING(info.getMaxPlayers()));
        itemServer->setText(5, TOSTRING(info.getPing()));

        m_TreeWidget->addTopLevelItem(itemServer);
        info.m_ptrItem = itemServer;
        info.m_IsShowed = true;

        m_TreeWidget->addTopLevelItem(info.m_ptrItem);
    }
    else
        delete &info;
}

void CServerManager::refreshList(bool reset)
{
    m_TreeWidget->clear();

    switch (m_SortFilter)
    {
    case SORT_HOSTNAME_DOWN:
        qSort(m_ServerList.begin(),
              m_ServerList.end(),
              [](CServerInfo &elem1, CServerInfo &elem2)->bool { return elem1.getHostName().toLower() > elem2.getHostName().toLower(); });
        break;

    case SORT_HOSTNAME_UP:
        qSort(m_ServerList.begin(),
              m_ServerList.end(),
              [](CServerInfo &elem1, CServerInfo &elem2)->bool { return elem1.getHostName().toLower() < elem2.getHostName().toLower(); });
        break;

    case SORT_ONLINE_PLAYERS:
        qSort(m_ServerList.begin(),
              m_ServerList.end(),
              [](CServerInfo &elem1, CServerInfo &elem2)->bool { return elem1.getOnlinePlayers() > elem2.getOnlinePlayers(); });
        break;

    case SORT_MAX_PLAYERS:
        qSort(m_ServerList.begin(),
              m_ServerList.end(),
              [](CServerInfo &elem1, CServerInfo &elem2)->bool { return elem1.getMaxPlayers() > elem2.getMaxPlayers(); });
        break;

    case SORT_PING:
        qSort(m_ServerList.begin(),
              m_ServerList.end(),
              [](CServerInfo &elem1, CServerInfo &elem2)->bool { return elem1.getPing() < elem2.getPing(); });
        break;
    }

    // Reset server data
    if (reset)
        for (CServerInfo &info : m_ServerList)
        {
            info.m_HostName = ServerUnknow::HOSTNAME;
            info.m_Description = ServerUnknow::DESCRIPTION;
            info.m_World = ServerUnknow::WORLD;
            info.m_Version = ServerUnknow::VERSION;
            info.m_Script = ServerUnknow::SCRIPT;
            info.m_OnlinePlayers = ServerUnknow::ONLINE_PLAYERS;
            info.m_MaxPlayers = ServerUnknow::MAX_PLAYERS;
            info.m_Ping = ServerUnknow::PING;
            info.m_IsShowed = false;
        }
}

void CServerManager::showRestServers()
{
    for (CServerInfo &info : m_ServerList)
        if (!info.m_IsShowed)
            insertServer(info.getIpAdress(), info.getPort());
}

void CServerManager::clear()
{
    m_TreeWidget->clear();
    m_ServerList.clear();
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Private method
//-------------------------------------------------------------------------------------------------------------------------------

void CServerManager::initConnections()
{
    connect(m_TreeWidget->header(), SIGNAL(sectionClicked(int)),
            this, SLOT(onHeaderItemClicked(int)));

    connect(m_TreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this, SLOT(onServerClicked(QTreeWidgetItem*,int)));

    connect(m_TreeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
            this, SLOT(onServerDoubleClicked(QTreeWidgetItem*,int)));
}

void CServerManager::updateInfo(QString ipAdress, QString port)
{
    CServerInfo &info = getServerInfo(ipAdress, port);

    if (info.exits())
    {
        LAUNCHER.getUI()->viewHostname->setText(TRANSLATE("SM_HOSTNAME") + info.getHostName());
        LAUNCHER.getUI()->viewIP->setText(TRANSLATE("SM_IP") + info.getIpAdress());
        LAUNCHER.getUI()->viewPort->setText(TRANSLATE("SM_PORT") + info.getPort());
        LAUNCHER.getUI()->viewWorld->setText(TRANSLATE("SM_WORLD") + info.getWorld());
        LAUNCHER.getUI()->viewVersion->setText(TRANSLATE("SM_VERSION") + info.getVersion());
        LAUNCHER.getUI()->viewOnlinePlayers->setText(TRANSLATE("SM_PLAYERS") + TOSTRING(info.getOnlinePlayers()) + "/" + TOSTRING(info.getMaxPlayers()));
        LAUNCHER.getUI()->viewPing->setText(TRANSLATE("SM_PING") + TOSTRING(info.getPing()));
        LAUNCHER.getUI()->viewDescription->setText(info.getDescription());
    }
    else
        delete &info;
}

bool CServerManager::updateXmlClient(CServerInfo serverInfo)
{
    // Generate new GO_Client.config.xml
    QFile configFile(CONFIG_GO_PATH);
    if(!configFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        CMessageBox::warrning(TRANSLATE("C_NAME"), TRANSLATE("C_WRITE_ERROR"));
        return false;
    }
    else
    {
        QTextStream stream(&configFile);
        stream << "<!-- Gothic Online automatic generated config file -->\n";
        stream << "<GO_Config>\n";
        stream << QString("\t<playerName>%1</playerName>\n").arg(LAUNCHER.getUI()->editNickname->text().isEmpty() ? "Nickname" : LAUNCHER.getUI()->editNickname->text());
        stream << QString("\t<serverIp>%1</serverIp>\n").arg(serverInfo.getIpAdress());
        stream << QString("\t<serverPort>%1</serverPort>\n").arg(serverInfo.getPort());
        stream << QString("\t<startWorld>%1</startWorld>\n").arg(serverInfo.getWorld());
        stream << QString("\t<playerInstance>%1</playerInstance>\n").arg("PC_HERO");
        stream << QString("\t<clientScript>%1</clientScript>\n").arg(serverInfo.getScript());
        stream << "</GO_Config>";

        configFile.close();
        return true;
    }
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Private slots
//-------------------------------------------------------------------------------------------------------------------------------

void CServerManager::onHeaderItemClicked(int index)
{
    switch (index)
    {
    case 0: // Hostname
        m_SortFilter = m_SortHostname ? SORT_HOSTNAME_DOWN : SORT_HOSTNAME_UP;
        m_SortHostname = !m_SortHostname;
        break;

    case 4: // Players
        m_SortFilter = m_SortPlayers ? SORT_ONLINE_PLAYERS : SORT_MAX_PLAYERS;
        m_SortPlayers = !m_SortPlayers;
        break;

    case 5: // Ping
        m_SortFilter = SORT_PING;
        break;
    }

    // Refresh list
    refreshList();

    // Fill server list
    for (CServerInfo &info : m_ServerList)
    {
        if (info.m_IsShowed)
        {
            QTreeWidgetItem *itemServer = new QTreeWidgetItem;
            itemServer->setText(0, info.getHostName());
            itemServer->setText(1, info.getIpAdress());
            itemServer->setText(2, info.getPort());
            itemServer->setText(3, info.getVersion());
            itemServer->setText(4, TOSTRING(info.getOnlinePlayers()) + "/" + TOSTRING(info.getMaxPlayers()));
            itemServer->setText(5, TOSTRING(info.getPing()));

            m_TreeWidget->addTopLevelItem(itemServer);
            info.m_ptrItem = itemServer;

            m_TreeWidget->addTopLevelItem(info.m_ptrItem);
        }
    }
}

void CServerManager::onServerClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column)

    updateInfo(item->text(1), item->text(2));
}

void CServerManager::onServerDoubleClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column)

    CServerInfo& info = getServerInfo(item->text(1), item->text(2));

    if (!info.exits())
        delete &info;
    else
        if (updateXmlClient(info))
            if (info.getOnlinePlayers() < info.getMaxPlayers())
                if (item->text(3).toStdString() == LAUNCHER.getString(VERSION_NAME_LENGHT, VERSION_NAME))
                    LAUNCHER.getNetwork().downloadServerFiles(item->text(0), item->text(1), item->text(2).toInt());
                else
                    CMessageBox::warrning(item->text(0), TRANSLATE("SM_WRONG_VERSION"));
            else if (info.getMaxPlayers() == 0)
                CMessageBox::warrning(item->text(0), TRANSLATE("SM_SERVER_OFFLINE"));
            else
                CMessageBox::warrning(item->text(0), TRANSLATE("SM_SERVER_FULL"));
}
