#include "PCH.h"

#ifdef DEBUG_MODE
#include <QMessageBox>
#endif

CFileTransferCallback::CFileTransferCallback() :
    m_NewFile(true),
    m_WasShowed(false),
    m_partCount(0),
    m_partTotal(0)
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Public method
//-------------------------------------------------------------------------------------------------------------------------------

void CFileTransferCallback::restart(bool show)
{
    m_NewFile = true;
    m_partCount = 0;
    m_partTotal = 0;

    if (show) m_WasShowed = false;
}


bool CFileTransferCallback::OnFile(OnFileStruct *fileStruct)
{
    assert(fileStruct->byteLengthOfThisFile >= fileStruct->bytesDownloadedForThisFile);
    restart();

    return true;
}

void CFileTransferCallback::OnFileProgress(FileProgressStruct *fileProgressStruct)
{
    assert(fileProgressStruct->onFileStruct->byteLengthOfThisFile >= fileProgressStruct->onFileStruct->bytesDownloadedForThisFile);

    if (!m_WasShowed)
    {
        m_WasShowed = true;
        emit onFileShow();
    }

    if (m_NewFile)
    {
        m_NewFile = false;
        m_partCount = fileProgressStruct->onFileStruct->bytesDownloadedForThisFile;
        m_partTotal = fileProgressStruct->onFileStruct->byteLengthOfThisFile;

        RakSleep(50); // Keep Qt GUI responsive
        emit onFileNew(m_partCount, m_partTotal,
                       fileProgressStruct->onFileStruct->bytesDownloadedForThisSet, fileProgressStruct->onFileStruct->byteLengthOfThisSet,
                       fileProgressStruct->onFileStruct->fileIndex + 1, fileProgressStruct->onFileStruct->numberOfFilesInThisSet,
                       QString(fileProgressStruct->onFileStruct->fileName));
    }
    else if (fileProgressStruct->onFileStruct->bytesDownloadedForThisFile > m_partCount)
    {
        m_partCount = fileProgressStruct->onFileStruct->bytesDownloadedForThisFile;
        emit onFileProgress(fileProgressStruct->onFileStruct->bytesDownloadedForThisFile, m_partTotal,
                            fileProgressStruct->onFileStruct->bytesDownloadedForThisSet, fileProgressStruct->onFileStruct->byteLengthOfThisSet);

        if (fileProgressStruct->onFileStruct->bytesDownloadedForThisFile == m_partTotal)
        {
            emit onFileSaved(fileProgressStruct->onFileStruct->fileIndex + 1,
                             fileProgressStruct->onFileStruct->numberOfFilesInThisSet,
                             fileProgressStruct->onFileStruct->fileName);
        }
    }
}

bool CFileTransferCallback::OnDownloadComplete(DownloadCompleteStruct *downloadCompleateStruct)
{
    Q_UNUSED(downloadCompleateStruct)

    m_WasShowed = false;
    restart();

    if (!NETWORK.getDownloaderRPC()->downloadNextSubDir())
        emit onFileDownloadComplete();

    return false;
}

