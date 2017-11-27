#ifndef CFAVORITE_MANAGER_H
#define CFAVORITE_MANAGER_H

#include <QObject>
#include <QVector>

#include "CFavorite.h"

class QTreeWidgetItem;

class CFavoriteManager : public QObject
{
    Q_OBJECT

public:
    explicit CFavoriteManager(QObject *parent = 0);
    ~CFavoriteManager();

    void translate();
    void saveFavoriteList();
    void loadFavoriteList();
    void serverList();

private:
    struct FavoriteServer
    {
        QString m_IP;
        QString m_Port;

        FavoriteServer() {}
        FavoriteServer(QString ipAdress, QString port) : m_IP(ipAdress), m_Port(port) {}

        bool operator== (const FavoriteServer& server) { return m_IP == server.m_IP && m_Port == server.m_Port; }
    };

    void initConnections();

    CFavorite m_Add, m_Edit;
    QTreeWidgetItem *m_TempEdit;
    QVector<FavoriteServer> m_ListFavorite;

private slots:
    void onButtonAddClicked();
    void onButtonEditClicked();
    void onButtonRemoveClicked();
    void onFavoriteAdd(QString host, QString port);
    void onFavoriteEdit(QString host, QString port);

friend class CNetwork;
};

#endif // CFAVORITE_H
