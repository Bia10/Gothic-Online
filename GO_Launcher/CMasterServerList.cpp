#include "PCH.h"

CMasterServerList::CMasterServerList(QThread &thread) :
    m_ThreadRunning(true)
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
    initConnections(thread);
    moveToThread(&thread);
}

CMasterServerList::~CMasterServerList()
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Public method
//-------------------------------------------------------------------------------------------------------------------------------

void CMasterServerList::setListData(const QString list)
{
    m_List = list;
}

void CMasterServerList::threadStop()
{
    m_ThreadRunning = false;
}

void CMasterServerList::threadRenew()
{
    m_ThreadRunning = true;
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Private method
//-------------------------------------------------------------------------------------------------------------------------------

void CMasterServerList::initConnections(QThread &thread)
{
    connect(&thread, SIGNAL(started()),
            this, SLOT(onSplitServersList()));
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Private slots
//-------------------------------------------------------------------------------------------------------------------------------

void CMasterServerList::onSplitServersList()
{
    QStringList serversData = m_List.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
    for (QString server : serversData)
    {
        if (!m_ThreadRunning)
        {
            m_ThreadRunning = true;
            return; // Quit from thread, correct way
        }

        QStringList serverInfo = server.split("_");

        if (serverInfo.size() >= 9) // Anti-crash, when server on list don't have enought fields
            emit signalAddServer(CServerInfo(serverInfo.at(0), serverInfo.at(1), serverInfo.at(2),
                                             serverInfo.at(5), serverInfo.at(7), serverInfo.at(8),
                                             serverInfo.at(6), serverInfo.at(3).toInt(), serverInfo.at(4).toInt()));

        QThread::msleep(20);
    }
}
