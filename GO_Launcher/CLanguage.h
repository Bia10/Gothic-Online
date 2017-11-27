#ifndef CLANGUAGE_H
#define CLANGUAGE_H

#include <QMap>
#include <QObject>

#define TRANSLATE(key) SLauncher::getInstance().getLanguage().getTranslate(key)

class CLanguage : public QObject
{
    Q_OBJECT

public:
    inline QString getCurrentLang() { return m_CurrLang; }

    void init();
    void setCurrentLang(QString lang);
    QString getTranslate(QString key);

private:
    QMap<QString, QMap<QString, QString> > m_Translate;
    QString m_CurrLang;

private slots:
    void onLanguageChanged(int index);
};

#endif // CLANGUAGE_H
