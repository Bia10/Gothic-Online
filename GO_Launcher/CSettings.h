#ifndef CSETTINGS_H
#define CSETTINGS_H

#include <QSettings>

class CSettings
{
public:
    CSettings();

    void loadLauncherSettings();
    void saveLauncherSettings();

private:
    QSettings m_LancherSetting;
};

#endif // CSETTINGS_H
