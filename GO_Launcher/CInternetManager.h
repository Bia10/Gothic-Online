#ifndef CINTERNETMANAGER_H
#define CINTERNETMANAGER_H

#include <QObject>
#include <QThread>
#include <QMap>

#include "CMessageBox.h"
#include "CMasterServerList.h"

#define MASTERSERVER_LINK_LENGHT 41

class CInternetManager : public QObject
{
    Q_OBJECT

public:
    CInternetManager();
    ~CInternetManager();

    void translate();
    void serverList();
    void clear();

private:
    void initConnections();
    void splitList(QString list);
    void showServers(QString list);
    void downloadError();
    void addServer(QString ipAdress, int port, int ping);

    QString m_MasterServerList;
    CMessageBox m_MsgBoxConnectionFailed, m_MsgBoxMasterServer;
    QThread m_SplitThread;
    CMasterServerList m_MasterServer;
    QMap<QString, CServerInfo> m_ServerList;

private slots:
    void onShowServer(CServerInfo serverInfo);

friend class CNetwork;
};

#endif // CINTERNETMANAGER_H
