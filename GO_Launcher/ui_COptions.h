/********************************************************************************
** Form generated from reading UI file 'COptions.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COPTIONS_H
#define UI_COPTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_COptions
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QGroupBox *gboxVideo;
    QGridLayout *gridLayout_2;
    QLabel *labelResolutionX;
    QSpinBox *spinResolutionX;
    QLabel *labelResolutionY;
    QSpinBox *spinResolutionY;
    QCheckBox *cboxWindowMode;
    QGroupBox *gboxSound;
    QGridLayout *gridLayout_3;
    QCheckBox *cboxSound;
    QSlider *sliderMusic;
    QCheckBox *cboxMusic;
    QSlider *sliderSound;
    QLabel *labelSound;
    QLabel *labelMusic;
    QPushButton *buttonSave;

    void setupUi(QWidget *COptions)
    {
        if (COptions->objectName().isEmpty())
            COptions->setObjectName(QStringLiteral("COptions"));
        COptions->resize(400, 380);
        gridLayoutWidget = new QWidget(COptions);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(9, 29, 381, 341));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gboxVideo = new QGroupBox(gridLayoutWidget);
        gboxVideo->setObjectName(QStringLiteral("gboxVideo"));
        gboxVideo->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_2 = new QGridLayout(gboxVideo);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        labelResolutionX = new QLabel(gboxVideo);
        labelResolutionX->setObjectName(QStringLiteral("labelResolutionX"));

        gridLayout_2->addWidget(labelResolutionX, 0, 0, 1, 1);

        spinResolutionX = new QSpinBox(gboxVideo);
        spinResolutionX->setObjectName(QStringLiteral("spinResolutionX"));
        spinResolutionX->setMinimum(800);
        spinResolutionX->setMaximum(5000);
        spinResolutionX->setDisplayIntegerBase(10);

        gridLayout_2->addWidget(spinResolutionX, 0, 1, 1, 1);

        labelResolutionY = new QLabel(gboxVideo);
        labelResolutionY->setObjectName(QStringLiteral("labelResolutionY"));

        gridLayout_2->addWidget(labelResolutionY, 1, 0, 1, 1);

        spinResolutionY = new QSpinBox(gboxVideo);
        spinResolutionY->setObjectName(QStringLiteral("spinResolutionY"));
        spinResolutionY->setMinimum(600);
        spinResolutionY->setMaximum(5000);

        gridLayout_2->addWidget(spinResolutionY, 1, 1, 1, 1);

        cboxWindowMode = new QCheckBox(gboxVideo);
        cboxWindowMode->setObjectName(QStringLiteral("cboxWindowMode"));

        gridLayout_2->addWidget(cboxWindowMode, 2, 0, 1, 2);


        gridLayout->addWidget(gboxVideo, 0, 0, 1, 1);

        gboxSound = new QGroupBox(gridLayoutWidget);
        gboxSound->setObjectName(QStringLiteral("gboxSound"));
        gridLayout_3 = new QGridLayout(gboxSound);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        cboxSound = new QCheckBox(gboxSound);
        cboxSound->setObjectName(QStringLiteral("cboxSound"));

        gridLayout_3->addWidget(cboxSound, 0, 0, 1, 1);

        sliderMusic = new QSlider(gboxSound);
        sliderMusic->setObjectName(QStringLiteral("sliderMusic"));
        sliderMusic->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(sliderMusic, 4, 0, 1, 2);

        cboxMusic = new QCheckBox(gboxSound);
        cboxMusic->setObjectName(QStringLiteral("cboxMusic"));

        gridLayout_3->addWidget(cboxMusic, 0, 1, 1, 1);

        sliderSound = new QSlider(gboxSound);
        sliderSound->setObjectName(QStringLiteral("sliderSound"));
        sliderSound->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(sliderSound, 2, 0, 1, 2);

        labelSound = new QLabel(gboxSound);
        labelSound->setObjectName(QStringLiteral("labelSound"));
        labelSound->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(labelSound, 1, 0, 1, 2);

        labelMusic = new QLabel(gboxSound);
        labelMusic->setObjectName(QStringLiteral("labelMusic"));
        labelMusic->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(labelMusic, 3, 0, 1, 2);


        gridLayout->addWidget(gboxSound, 1, 0, 1, 1);

        buttonSave = new QPushButton(gridLayoutWidget);
        buttonSave->setObjectName(QStringLiteral("buttonSave"));

        gridLayout->addWidget(buttonSave, 2, 0, 1, 1);


        retranslateUi(COptions);

        QMetaObject::connectSlotsByName(COptions);
    } // setupUi

    void retranslateUi(QWidget *COptions)
    {
        COptions->setWindowTitle(QApplication::translate("COptions", "Form", 0));
        gboxVideo->setTitle(QApplication::translate("COptions", "GroupBox", 0));
        labelResolutionX->setText(QApplication::translate("COptions", "TextLabel", 0));
        labelResolutionY->setText(QApplication::translate("COptions", "TextLabel", 0));
        cboxWindowMode->setText(QApplication::translate("COptions", "CheckBox", 0));
        gboxSound->setTitle(QApplication::translate("COptions", "GroupBox", 0));
        cboxSound->setText(QApplication::translate("COptions", "CheckBox", 0));
        cboxMusic->setText(QApplication::translate("COptions", "CheckBox", 0));
        labelSound->setText(QApplication::translate("COptions", "TextLabel", 0));
        labelMusic->setText(QApplication::translate("COptions", "TextLabel", 0));
        buttonSave->setText(QApplication::translate("COptions", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class COptions: public Ui_COptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPTIONS_H
