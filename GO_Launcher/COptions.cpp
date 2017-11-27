#include "PCH.h"

COptions::COptions(QWidget *parent) :
    CCustomWindow(QString(":/img/go_widget.png"), parent, BUTTON_CLOSE),
    m_GothicSetting("../System/Gothic.ini", QSettings::IniFormat),
    ui(new Ui::COptions)
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
    ui->setupUi(this);

    setWindowTitle("Options");

    initWidgets();
    initConnections();
    translate();
    loadGothicSettings();
}

COptions::~COptions()
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
    delete ui;
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Public method
//-------------------------------------------------------------------------------------------------------------------------------

void COptions::translate()
{
    ui->gboxVideo->setTitle(TRANSLATE("O_VIDEO"));

    ui->labelResolutionX->setText(TRANSLATE("O_RES_X"));
    ui->labelResolutionY->setText(TRANSLATE("O_RES_Y"));
    ui->cboxWindowMode->setText(TRANSLATE("O_WINDOW_MODE"));

    ui->gboxSound->setTitle(TRANSLATE("O_GBOX_SOUND"));

    ui->cboxSound->setText(TRANSLATE("O_ESOUND"));
    ui->cboxMusic->setText(TRANSLATE("O_EMUSIC"));
    ui->labelSound->setText(TRANSLATE("O_SOUND"));
    ui->labelMusic->setText(TRANSLATE("O_MUSIC"));

    ui->buttonSave->setText(TRANSLATE("O_SAVE"));
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Public slots
//-------------------------------------------------------------------------------------------------------------------------------

void COptions::customShow()
{
    // Video
    ui->spinResolutionX->setValue(m_GothicConfig.zVidResFullscreenX);
    ui->spinResolutionY->setValue(m_GothicConfig.zVidResFullscreenY);
    ui->cboxWindowMode->setChecked(m_GothicConfig.zStartupWindowed);

    // Sound
    ui->cboxSound->setChecked(m_GothicConfig.soundEnabled);
    ui->cboxMusic->setChecked(m_GothicConfig.musicEnabled);

    ui->sliderSound->setValue(m_GothicConfig.soundVolume * 100);
    ui->sliderMusic->setValue(m_GothicConfig.musicVolume * 100);

    show();
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Private method
//-------------------------------------------------------------------------------------------------------------------------------

void COptions::initWidgets()
{
}

void COptions::initConnections()
{
    connect(this, SIGNAL(Style_quit()),
            this, SLOT(hide()));

    connect(ui->buttonSave, SIGNAL(released()),
            this, SLOT(onButtonSaveClicked()));
}

void COptions::loadGothicSettings()
{
    m_GothicSetting.beginGroup("VIDEO");
    m_GothicConfig.zVidResFullscreenX = m_GothicSetting.value("zVidResFullscreenX", 800).toInt();
    m_GothicConfig.zVidResFullscreenY = m_GothicSetting.value("zVidResFullscreenY", 600).toInt();
    m_GothicConfig.zStartupWindowed = m_GothicSetting.value("zStartupWindowed", false).toBool();
    m_GothicSetting.endGroup();

    m_GothicSetting.beginGroup("SOUND");
    m_GothicConfig.soundVolume = m_GothicSetting.value("soundVolume", 1.0).toDouble();
    m_GothicConfig.musicVolume = m_GothicSetting.value("musicVolume", 1.0).toDouble();
    m_GothicConfig.soundEnabled = m_GothicSetting.value("soundEnabled", true).toBool();
    m_GothicConfig.musicEnabled = m_GothicSetting.value("musicEnabled", true).toBool();
    m_GothicSetting.endGroup();
}

void COptions::saveGothicSettings()
{
    m_GothicSetting.beginGroup("VIDEO");
    m_GothicSetting.setValue("zVidResFullscreenX", m_GothicConfig.zVidResFullscreenX);
    m_GothicSetting.setValue("zVidResFullscreenY", m_GothicConfig.zVidResFullscreenY);
    m_GothicSetting.setValue("zStartupWindowed", m_GothicConfig.zStartupWindowed ? 1 : 0);
    m_GothicSetting.endGroup();

    m_GothicSetting.beginGroup("SOUND");
    m_GothicSetting.setValue("soundVolume", m_GothicConfig.soundVolume);
    m_GothicSetting.setValue("musicVolume", m_GothicConfig.musicVolume);
    m_GothicSetting.setValue("soundEnabled", m_GothicConfig.soundEnabled ? 1 : 0);
    m_GothicSetting.setValue("musicEnabled", m_GothicConfig.musicEnabled ? 1 : 0);
    m_GothicSetting.endGroup();
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Private slots
//-------------------------------------------------------------------------------------------------------------------------------

void COptions::onButtonSaveClicked()
{
    // Video
    m_GothicConfig.zVidResFullscreenX = ui->spinResolutionX->value();
    m_GothicConfig.zVidResFullscreenY = ui->spinResolutionY->value();
    m_GothicConfig.zStartupWindowed = ui->cboxWindowMode->isChecked();

    // Sound
    m_GothicConfig.soundEnabled = ui->cboxSound->isChecked();
    m_GothicConfig.musicEnabled = ui->cboxMusic->isChecked();

    m_GothicConfig.soundVolume = ui->sliderSound->value() / 100.0f;
    m_GothicConfig.musicVolume = ui->sliderMusic->value() / 100.0f;

    saveGothicSettings();
}
