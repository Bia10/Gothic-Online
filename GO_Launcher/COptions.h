#ifndef COPTIONS_H
#define COPTIONS_H

#include <QSettings>

#include "Style/CCustomWindow.h"

namespace Ui {
    class COptions;
}

class COptions : public CCustomWindow
{
    Q_OBJECT

public:
    explicit COptions(QWidget *parent = 0);
    ~COptions();

     void translate();

public slots:
    void customShow();

private:
    struct
    {
        int    zVidResFullscreenX, zVidResFullscreenY;
        double soundVolume, musicVolume;
        bool   zStartupWindowed, soundEnabled, musicEnabled;
    } m_GothicConfig;

    void initWidgets();
    void initConnections();

    void loadGothicSettings();
    void saveGothicSettings();

    Ui::COptions *ui;
    QSettings m_GothicSetting;

private slots:
    void onButtonSaveClicked();
};

#endif // COPTIONS_H
