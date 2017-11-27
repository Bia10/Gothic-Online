#ifndef CMASTERSERVERLIST_H
#define CMASTERSERVERLIST_H

#include <QObject>
#include <QStringList>
#include <QThread>
#include <QMap>

#include "CServerInfo.h"

class CMasterServerList : public QObject
{
    Q_OBJECT

signals:
    void signalAddServer(CServerInfo serversInfo);

public:
    CMasterServerList(QThread &thread);
    ~CMasterServerList();

    void setListData(const QString list);
    void threadStop();
    void threadRenew();

private:
    void initConnections(QThread &thread);

    QString m_List;
    bool m_ThreadRunning;

private slots:
    void onSplitServersList();
};

#endif // CMASTERSERVERLIST_H
