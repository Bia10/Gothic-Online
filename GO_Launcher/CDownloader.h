#ifndef CDOWNLOADER_H
#define CDOWNLOADER_H

#include <QTime>

#include "Style/CCustomWindow.h"
#include "CMessageBox.h"

namespace Ui {
    class CDownloader;
}

class CDownloader : public CCustomWindow
{
    Q_OBJECT

public:
    explicit CDownloader(QWidget *parent = 0);
    ~CDownloader();

    void translate();
    void show();
    void setupFile(unsigned partCount, unsigned partTotal, unsigned totalCount, unsigned totalSize, unsigned fileIndex, unsigned filesAmount, QString fileName);
    void updateFileProgress(unsigned partCount, unsigned partTotal, unsigned totalCount, unsigned totalSize);
    void saveFile(unsigned fileIndex, unsigned filesAmount, QString fileName);

public slots:
    void onWait();
    void onQuit();

private:
    void initConnections();

    Ui::CDownloader *ui;
    CMessageBox m_DownloaderWait;
    QTime m_DownloadTime;
};

#endif // CDOWNLOADER_H
