#include "PCH.h"

CVersion::CVersion()
    : m_VersionUrl(LAUNCHER.cryptString(VERSION_LINK_LENGHT, VERSION_LINK).c_str()),
      m_Showed(false)
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Public method
//-------------------------------------------------------------------------------------------------------------------------------

void CVersion::checkUpdates()
{
    LAUNCHER.getNetwork().downloadFileFromUrl(LAUNCHER.decryptString(m_VersionUrl.toStdString()).c_str(), FILE_URL_VERSION);
}

void CVersion::updateVersionInfo(QString version)
{
    m_VersionInfo = version.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);

    if (m_Showed)
        checkVersion();
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Public slots
//-------------------------------------------------------------------------------------------------------------------------------

void CVersion::checkVersion()
{
    if (m_VersionInfo.size() > 0)
    {
        // id 0 = version | id 1 = link | id 2 = author's message
        if (LAUNCHER.getVersion() != m_VersionInfo.at(0))
        {
            QString message = TRANSLATE("V_NEW_AVAILABLE").arg(m_VersionInfo.at(0)).arg(m_VersionInfo.at(1));

            if (m_VersionInfo.size() > 2)
                message.append("<br><br>" + TRANSLATE("V_INFORMATION") + "<br>" + m_VersionInfo.at(2));

            CMessageBox::warrning(APP_NAME, message);
        }
    }
    else
        m_Showed = true;
}
