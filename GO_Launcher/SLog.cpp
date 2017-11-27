#include <QDate>
#include <QTime>
#include <QDir>

#include <cstdarg>

#include "PCH.h"
// [HH:mm:ss t]
SLog::SLog() :
    m_LogFile(QDate::currentDate().toString("Log/dd_MM_yy.log")),
    isOpen(false)
{
    if (!QDir("Log").exists())
        QDir().mkdir("Log");

    if (!m_LogFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        CMessageBox::warrning("Logger", "Cannot create log file!");
        return;
    }

    isOpen = true;
}

SLog::~SLog()
{
    if (isOpen)
        m_LogFile.close();
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Public method
//-------------------------------------------------------------------------------------------------------------------------------

SLog& SLog::getInstance()
{
    static SLog instance;
    return instance;
}

void SLog::entryLog(const char *format, ...)
{
    char logContent[512];
    QString qFormat = QTime::currentTime().toString("[HH:mm:ss]") + format;

    va_list args;
    va_start(args, format);
    std::vsprintf(logContent, qFormat.toStdString().c_str(), args);
    va_end(args);

    qDebug() << logContent;

    m_LogFile.write(logContent);
    m_LogFile.write("\n");
    m_LogFile.flush();
}

