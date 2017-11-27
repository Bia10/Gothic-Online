#include <QDesktopWidget>

#include "PCH.h"

CSettings::CSettings() :
    m_LancherSetting(CONFIG_PATH, QSettings::IniFormat)
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
    qApp->setApplicationName(APP_NAME);
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Public method
//-------------------------------------------------------------------------------------------------------------------------------

void CSettings::loadLauncherSettings()
{
    QDesktopWidget *desktop = QApplication::desktop();

    LAUNCHER.getUI()->editNickname->setText(m_LancherSetting.value("nickname", SettingUnknow::NAME).toString());
    LAUNCHER.move(m_LancherSetting.value("pos-x", (desktop->width() / 2) - (LAUNCHER.width() / 2)).toInt(),
                  m_LancherSetting.value("pos-y", (desktop->height() / 2) - (LAUNCHER.height() / 2)).toInt());
    LAUNCHER.getLanguage().setCurrentLang(m_LancherSetting.value("lang").toString());
}

void CSettings::saveLauncherSettings()
{
    m_LancherSetting.setValue("nickname", LAUNCHER.getUI()->editNickname->text().isEmpty() ? SettingUnknow::NAME : LAUNCHER.getUI()->editNickname->text());
    m_LancherSetting.setValue("pos-x", LAUNCHER.x());
    m_LancherSetting.setValue("pos-y", LAUNCHER.y());
    m_LancherSetting.setValue("lang", LAUNCHER.getLanguage().getCurrentLang());
}
