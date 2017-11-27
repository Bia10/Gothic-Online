#ifndef CVERSION_H
#define CVERSION_H

#include <QObject>
#include <QStringList>

class CVersion : public QObject
{

    Q_OBJECT

public:
    CVersion();

    void checkUpdates();
    void updateVersionInfo(QString version);

public slots:
    void checkVersion();

private:
    QString m_VersionUrl;
    QStringList m_VersionInfo;
    bool m_Showed;
};

#endif // CVERSION_H
