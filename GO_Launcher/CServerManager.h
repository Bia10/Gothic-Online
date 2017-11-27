#ifndef CSERVERMANAGER_H
#define CSERVERMANAGER_H

#include <QObject>
#include <QVector>
#include <QTreeWidget>

#include "CServerInfo.h"

class QTreeWidgetItem;

class CServerManager : public QObject
{
    Q_OBJECT

public:
    enum ESortFilter
    {
        SORT_NONE,
        SORT_HOSTNAME_DOWN,
        SORT_HOSTNAME_UP,
        SORT_ONLINE_PLAYERS,
        SORT_MAX_PLAYERS,
        SORT_PING,
    };

    CServerManager(QTreeWidget *treeWidget);

    static void  fillServerInfo();

    inline QVector<CServerInfo> getServerList() { return m_ServerList; }

    CServerInfo& getServerInfo(QString ipAdress, QString port);
    void 		 addServer(CServerInfo &serverInfo, bool show = true);
    void 		 removeServer(QString ipAdress, QString port);
    void		 editServer(QString ipAdress, QString port, QString newIpAdress, QString newPort);
    void         insertServer(QString ipAdress, QString port, QString hostName, QString descripion, QString script, QString world, QString version,
                              int onlinePlayers, int maxPlayers, int ping);
    void         insertServer(QString ipAdress, QString port);
    void         refreshList(bool reset = false);
    void         showRestServers();
    void         clear();

private:
    void initConnections();
    void updateInfo(QString ipAdress, QString port);
    bool updateXmlClient(CServerInfo serverInfo);

    QVector<CServerInfo> m_ServerList;
    QTreeWidget *m_TreeWidget;
    ESortFilter m_SortFilter;

    bool m_SortHostname, m_SortPlayers;

private slots:
    void onHeaderItemClicked(int index);
    void onServerClicked(QTreeWidgetItem *item, int column);
    void onServerDoubleClicked(QTreeWidgetItem *item, int column);
};

#endif // CSERVERMANAGER_H
