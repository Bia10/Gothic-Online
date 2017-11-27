#ifndef CFILETRANSFERCALLBACK_H
#define CFILETRANSFERCALLBACK_H

#include <QObject>

#include <FileListTransferCBInterface.h>

class CFileTransferCallback : public QObject, public RakNet::FileListTransferCBInterface
{
    Q_OBJECT

signals:
    void onFileShow();
    void onFileSaved(unsigned fileIndex, unsigned filesAmount, QString fileName);
    void onFileNew(unsigned partCount, unsigned partTotal, unsigned totalCount, unsigned totalSize, unsigned fileIndex, unsigned filesAmount, QString fileName);
    void onFileProgress(unsigned partCount, unsigned partTotal, unsigned totalCount, unsigned totalSize);
    void onFileDownloadComplete();

public:
    CFileTransferCallback();

    bool OnFile(OnFileStruct *fileStruct);

    void restart(bool show = false);
    virtual void OnFileProgress(FileProgressStruct *fileProgressStruct);
    virtual bool OnDownloadComplete(DownloadCompleteStruct *downloadCompleateStruct);

private:
    bool m_NewFile, m_WasShowed;
    ulong m_partCount, m_partTotal;
};

#endif // CFILETRANSFERCALLBACK_H
