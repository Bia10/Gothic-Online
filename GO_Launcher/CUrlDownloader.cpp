#include "PCH.h"

CUrlDownloader::CUrlDownloader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CUrlDownloader),
    m_Downloading(false)
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
    ui->setupUi(this);

    connect(&m_NetworkManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(onDownloadFinished(QNetworkReply*)));
}

CUrlDownloader::~CUrlDownloader()
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
    delete ui;
}

void CUrlDownloader::downloadFile(QString url)
{
    if (!m_Downloading)
    {
        const QNetworkRequest networkRequest(QUrl(url.toStdString().c_str()));

        m_NetworkReply = m_NetworkManager.get(networkRequest);

        connect(m_NetworkReply, SIGNAL(downloadProgress(qint64, qint64)),
                this, SLOT(onDownloadProgress(qint64,qint64)));

        connect(m_NetworkReply, SIGNAL(error(QNetworkReply::NetworkError)),
                this, SLOT(onError(QNetworkReply::NetworkError)));

        connect(m_NetworkReply, SIGNAL(finished()),
                this, SLOT(onReplyDelete()));

        m_Downloading = true;
    }
}


void CUrlDownloader::onReplyDelete()
{
    disconnect(m_NetworkReply, SIGNAL(downloadProgress(qint64, qint64)),
               this, SLOT(onDownloadProgress(qint64,qint64)));

    disconnect(m_NetworkReply, SIGNAL(error(QNetworkReply::NetworkError)),
              this, SLOT(onError(QNetworkReply::NetworkError)));

    disconnect(m_NetworkReply, SIGNAL(finished()),
               this, SLOT(onReplyDelete()));

    m_NetworkReply->deleteLater();
    m_Downloading = false;
}

void CUrlDownloader::onDownloadFinished(QNetworkReply *data)
{
    m_Cache = QString(data->readAll());
    emit signalDownloadCompleteCache(m_Cache);
}

void CUrlDownloader::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    Q_UNUSED(bytesReceived)
    Q_UNUSED(bytesTotal)
}

void CUrlDownloader::onError(QNetworkReply::NetworkError error)
{
    Q_UNUSED(error)
    emit signalError();
}
