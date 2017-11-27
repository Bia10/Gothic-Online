#ifndef CURLDOWNLOADER_H
#define CURLDOWNLOADER_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTime>

/*
 *  NOTE!
 *  This class isn't finished yet, but for now is enought.
 */

namespace Ui {
    class CUrlDownloader;
}

class CUrlDownloader : public QWidget
{
    Q_OBJECT

signals:
    void signalDownloadCompleteCache(QString cache);
    void signalError();

public:
    explicit CUrlDownloader(QWidget *parent = 0);
    ~CUrlDownloader();

    void downloadFile(QString url);

private:
    Ui::CUrlDownloader *ui;

    QNetworkAccessManager m_NetworkManager;
    QNetworkReply *m_NetworkReply;
    QString m_Cache;
    bool m_Downloading;

private slots:
    void onReplyDelete();
    void onDownloadFinished(QNetworkReply *data);
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void onError(QNetworkReply::NetworkError error);
};

#endif // CURLDOWNLOADER_H
