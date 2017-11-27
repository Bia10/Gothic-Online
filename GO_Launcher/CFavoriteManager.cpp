#include <fstream>

#include "PCH.h"

CFavoriteManager::CFavoriteManager(QObject *parent) :
    QObject(parent),
    m_TempEdit(NULL)
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
    initConnections();
}

CFavoriteManager::~CFavoriteManager()
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
    saveFavoriteList();
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Public method
//-------------------------------------------------------------------------------------------------------------------------------

void CFavoriteManager::translate()
{
    m_Add.setWindowTitle(TRANSLATE("F_WADD"));
    m_Edit.setWindowTitle(TRANSLATE("F_WREMOVE"));

    m_Add.translate();
    m_Edit.translate();
}

void CFavoriteManager::saveFavoriteList()
{
    std::ofstream favoriteList;
    favoriteList.open(FAVORITE_PATH, std::ios::out | std::ios::binary);

    if (favoriteList.is_open())
    {
        int listSize = m_ListFavorite.size();
        favoriteList.write(reinterpret_cast<char*>(&listSize), sizeof(listSize));

        for (FavoriteServer &server : m_ListFavorite)
        {
            std::string ipAdress = server.m_IP.toStdString(), port = server.m_Port.toStdString();
            int ipLenght = ipAdress.length(), portLenght = port.length();

            // Simply XOR
            favoriteList.write(reinterpret_cast<char*>(&ipLenght), sizeof(ipLenght));
            for (int i = 0; i < ipLenght; ++i)
            {
                ipAdress[i] ^= 0x1E;
                favoriteList.write(&ipAdress[i], sizeof(char));
            }

            favoriteList.write(reinterpret_cast<char*>(&portLenght), sizeof(portLenght));
            for (int i = 0; i < portLenght; ++i)
            {
                port[i] ^= 0x1E;
                favoriteList.write(&port[i], sizeof(char));
            }
        }
        favoriteList.close();
    }
}

void CFavoriteManager::loadFavoriteList()
{
    std::ifstream favoriteList;
    favoriteList.open(FAVORITE_PATH, std::ios::in | std::ios::binary);

    if (favoriteList.is_open())
    {
        int listSize = NULL;
        favoriteList.read(reinterpret_cast<char*>(&listSize), sizeof(listSize));

        for (int amount = 0; amount < listSize; ++amount)
        {
            int ipLenght = NULL, portLenght = NULL;
            QString ipAdress = "", port = "";

            char buff;

            favoriteList.read(reinterpret_cast<char*>(&ipLenght), sizeof(ipLenght));
            for (int i = 0; i < ipLenght; ++i)
            {
                favoriteList.read(&buff, sizeof(char));
                ipAdress += (buff ^ 0x1E);
            }

            favoriteList.read(reinterpret_cast<char*>(&portLenght), sizeof(portLenght));
            for (int i = 0; i < portLenght; ++i)
            {
                favoriteList.read(&buff, sizeof(char));
                port += (buff ^ 0x1E);
            }

            // Append data to Vector
            LAUNCHER.getServerFavoriteManager()->addServer(CServerInfo(ipAdress, port));
            m_ListFavorite.append(FavoriteServer(ipAdress, port));
        }

        favoriteList.close();
    }
}

void CFavoriteManager::serverList()
{
    LAUNCHER.getServerFavoriteManager()->refreshList(true);
    LAUNCHER.getNetwork().sendRequest(LAUNCHER.getServerFavoriteManager()->getServerList(), INDEX_FAVORITE);
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Private method
//-------------------------------------------------------------------------------------------------------------------------------

void CFavoriteManager::initConnections()
{
    connect(&m_Add, SIGNAL(signalButtonOkClicked(QString,QString)),
            this, SLOT(onFavoriteAdd(QString,QString)));

    connect(&m_Edit, SIGNAL(signalButtonOkClicked(QString,QString)),
            this, SLOT(onFavoriteEdit(QString,QString)));
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Private slots
//-------------------------------------------------------------------------------------------------------------------------------

void CFavoriteManager::onButtonAddClicked()
{
    m_Add.show();
}

void CFavoriteManager::onButtonEditClicked()
{
    QTreeWidgetItem *server = LAUNCHER.getUI()->treeFavorite->currentItem();
    if (!server) return;

    m_TempEdit = server;

    m_Edit.ui->editIP->setText(server->text(1) + ":" + server->text(2));
    m_Edit.show();
}

void CFavoriteManager::onButtonRemoveClicked()
{
    QTreeWidgetItem *server = LAUNCHER.getUI()->treeFavorite->currentItem();
    if (!server) return;

    m_ListFavorite.removeOne(FavoriteServer(server->text(1), server->text(2)));
    LAUNCHER.getServerFavoriteManager()->removeServer(server->text(1), server->text(2));
}

void CFavoriteManager::onFavoriteAdd(QString host, QString port)
{
    LAUNCHER.getServerFavoriteManager()->addServer(CServerInfo(host, port));

    if (!m_ListFavorite.contains(FavoriteServer(host, port))) m_ListFavorite.append(FavoriteServer(host, port));
}

void CFavoriteManager::onFavoriteEdit(QString host, QString port)
{
    int index = m_ListFavorite.indexOf(FavoriteServer(m_TempEdit->text(1), m_TempEdit->text(2)));
    if (index != -1)
    {
        m_ListFavorite[index].m_IP = host;
        m_ListFavorite[index].m_Port = port;
    }

    LAUNCHER.getServerFavoriteManager()->editServer(m_TempEdit->text(1), m_TempEdit->text(2), host, port);
}
