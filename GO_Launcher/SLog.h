#ifndef SLOG_H
#define SLOG_H

#include <QFile>
#include <memory>

#define LOG(format, ...) SLog::getInstance().entryLog(format, __VA_ARGS__);

class SLog
{
public:
    SLog();
    ~SLog();

    static SLog& getInstance();

    void entryLog(const char *format, ...);

private:
    QFile m_LogFile;
    bool isOpen;
};

#endif // SLOG_H
