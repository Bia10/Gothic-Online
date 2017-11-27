/********************************************************************************
** Form generated from reading UI file 'CMessageBox.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMESSAGEBOX_H
#define UI_CMESSAGEBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMessageBox
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *buttonOk;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QLabel *labelMessage;

    void setupUi(QWidget *CMessageBox)
    {
        if (CMessageBox->objectName().isEmpty())
            CMessageBox->setObjectName(QStringLiteral("CMessageBox"));
        CMessageBox->resize(380, 140);
        gridLayoutWidget = new QWidget(CMessageBox);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 30, 361, 101));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        buttonOk = new QPushButton(gridLayoutWidget);
        buttonOk->setObjectName(QStringLiteral("buttonOk"));
        buttonOk->setMinimumSize(QSize(80, 0));
        buttonOk->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(buttonOk, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        labelMessage = new QLabel(gridLayoutWidget);
        labelMessage->setObjectName(QStringLiteral("labelMessage"));
        labelMessage->setTextFormat(Qt::RichText);
        labelMessage->setAlignment(Qt::AlignCenter);
        labelMessage->setOpenExternalLinks(true);

        gridLayout->addWidget(labelMessage, 0, 0, 1, 3);


        retranslateUi(CMessageBox);

        QMetaObject::connectSlotsByName(CMessageBox);
    } // setupUi

    void retranslateUi(QWidget *CMessageBox)
    {
        CMessageBox->setWindowTitle(QApplication::translate("CMessageBox", "Form", 0));
        buttonOk->setText(QApplication::translate("CMessageBox", "Ok", 0));
        labelMessage->setText(QApplication::translate("CMessageBox", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class CMessageBox: public Ui_CMessageBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMESSAGEBOX_H
