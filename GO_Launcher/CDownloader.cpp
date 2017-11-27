#include "PCH.h"

CDownloader::CDownloader(QWidget *parent) :
    CCustomWindow(QColor("#333"), NULL, BUTTON_CLOSE, QSize(400, 160), true),
    ui(new Ui::CDownloader)
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
    Q_UNUSED(parent)

    ui->setupUi(this);

    initConnections();
}

CDownloader::~CDownloader()
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
    delete ui;
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Public method
//-------------------------------------------------------------------------------------------------------------------------------

void CDownloader::translate()
{
    m_DownloaderWait.setWindowTitle(TRANSLATE("D_NAME"));
    m_DownloaderWait.setText(TRANSLATE("D_QUIT"));
}

void CDownloader::show()
{
    ui->labelTotalSize->setText(QString(TRANSLATE("D_TOTAL_SIZE")).arg(0).arg(0).arg("B"));
    ui->labelSize->setText(QString(TRANSLATE("D_FILE_SIZE")).arg(0).arg(0).arg("B"));
    ui->labelInfo->setText(QString(TRANSLATE("D_DOWNLOAD_FILE")).arg(0).arg(0).arg("unknow"));
    ui->labelSpeed->setText("0 B/s");

    CCustomWindow::show();
}


void CDownloader::setupFile(unsigned partCount, unsigned partTotal, unsigned totalCount, unsigned totalSize, unsigned fileIndex, unsigned filesAmount, QString fileName)
{
    ui->progressBar->setRange(0, partTotal);
    ui->progressBar->setValue(partCount);

    ui->progressBarTotal->setRange(0, totalSize);
    ui->progressBarTotal->setValue(totalCount);

    ui->labelTotalSize->setText(QString(TRANSLATE("D_TOTAL_SIZE")).arg(totalCount).arg(totalSize).arg("B"));
    ui->labelSize->setText(QString(TRANSLATE("D_FILE_SIZE")).arg(partCount).arg(partTotal).arg("B"));
    ui->labelInfo->setText(QString(TRANSLATE("D_DOWNLOAD_FILE")).arg(fileIndex).arg(filesAmount).arg(fileName));

    m_DownloadTime.start();
}

void CDownloader::updateFileProgress(unsigned partCount, unsigned partTotal, unsigned totalCount, unsigned totalSize)
{
    ui->progressBar->setValue(partCount);
    ui->progressBarTotal->setValue(totalCount);

    uint speed = partCount * 1000.0 / m_DownloadTime.elapsed();
    QString unitSpeed;
    if (speed < 1024)
    {
        unitSpeed = "B/s";
    }
    else if (speed < 1024 * 1024)
    {
        speed /= 1024;
        unitSpeed = "KB/s";
    }
    else
    {
        speed /= 1024 * 1024;
        unitSpeed = "MB/s";
    }

    ui->labelSpeed->setText(TOSTRING(speed) + " " + unitSpeed);

    QString receivedSizeUnit;
    if (partCount < 1024)
    {
        receivedSizeUnit = "B";
    }
    else if (partCount < 1024 * 1024)
    {
        partCount /= 1024;
        partTotal /= 1024;
        receivedSizeUnit = "KB";
    }
    else
    {
        partCount /= 1024 * 1024;
        partTotal /= 1024 * 1024;;
        receivedSizeUnit = "MB";
    }

    ui->labelSize->setText(QString(TRANSLATE("D_FILE_SIZE")).arg(partCount).arg(partTotal).arg(receivedSizeUnit));

    if (totalCount < 1024)
    {
        receivedSizeUnit = "B";
    }
    else if (totalCount < 1024 * 1024)
    {
        totalCount /= 1024;
        totalSize /= 1024;
        receivedSizeUnit = "KB";
    }
    else
    {
        totalCount /= 1024 * 1024;
        totalSize /= 1024 * 1024;;
        receivedSizeUnit = "MB";
    }

    ui->labelTotalSize->setText(QString(TRANSLATE("D_TOTAL_SIZE")).arg(totalCount).arg(totalSize).arg(receivedSizeUnit));
}

void CDownloader::saveFile(unsigned fileIndex, unsigned filesAmount, QString fileName)
{
    ui->labelInfo->setText(QString(TRANSLATE("D_SAVE_FILE")).arg(fileIndex).arg(filesAmount).arg(fileName));
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Public slots
//-------------------------------------------------------------------------------------------------------------------------------

void CDownloader::onWait()
{
    NETWORK.disconnectFromCurrent(true);

    m_DownloaderWait.show();
}

void CDownloader::onQuit()
{
    close();

    m_DownloaderWait.close();
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Private method
//-------------------------------------------------------------------------------------------------------------------------------

void CDownloader::initConnections()
{
    connect(this, SIGNAL(Style_quit()),
            this, SLOT(onWait()));
}
