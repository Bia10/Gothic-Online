#include <QSettings>
#include <QFile>
#include <QTextStream>

#include "PCH.h"

//-------------------------------------------------------------------------------------------------------------------------------
//  Public method
//-------------------------------------------------------------------------------------------------------------------------------

void CLanguage::init()
{
    QSettings langConf("lang/lang.conf", QSettings::IniFormat);
    QStringList langList = langConf.value("lang").toString().split(QRegExp("\\s"));

    for (QString lang : langList)
    {
        QFile fileLang("lang/translate/" + lang + ".lang");
        if (fileLang.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream stream(&fileLang);
            QString line;

            do
            {
                line = stream.readLine();

                if (!line.isEmpty() && line.at(0) != '#') // Comment
                {
                    char key[100], translate[500];
                    std::sscanf(line.toStdString().c_str(), "%s%[^\n]", key, translate);

                    QString strTranslate = translate;
                    strTranslate.replace(QRegExp("[\t]"), "");

                    // Remove spaces, before text
                    while (strTranslate.at(0) == ' ')
                        strTranslate.remove(0, 1);

                    m_Translate[lang][key] = strTranslate;
                }
            } while (!line.isNull());

            LAUNCHER.getUI()->cboxLanguage->addItem(QIcon("lang/icons/" + lang + ".png"), m_Translate[lang]["LANG_NAME"], lang);

            fileLang.close();
        }
    }

    connect(LAUNCHER.getUI()->cboxLanguage, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onLanguageChanged(int)));

    // Fill empty language
    if (m_CurrLang.isEmpty() && !langList.empty()) m_CurrLang = langList.at(0);

    // Find index in language list
    int index = LAUNCHER.getUI()->cboxLanguage->findData(m_CurrLang);
    if (index != -1)
       LAUNCHER.getUI()->cboxLanguage->setCurrentIndex(index);
}

void CLanguage::setCurrentLang(QString lang)
{
    m_CurrLang = lang;
}

QString CLanguage::getTranslate(QString key)
{
    if (m_Translate.contains(m_CurrLang) && m_Translate[m_CurrLang].contains(key))
        return m_Translate[m_CurrLang][key];

    return "EMPTY";
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Private slots
//-------------------------------------------------------------------------------------------------------------------------------

void CLanguage::onLanguageChanged(int index)
{
    Q_UNUSED(index)
    m_CurrLang = LAUNCHER.getUI()->cboxLanguage->currentData().toString();
    LAUNCHER.translate();
}
