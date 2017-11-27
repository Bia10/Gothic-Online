/********************************************************************************
** Form generated from reading UI file 'CFavorite.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CFAVORITE_H
#define UI_CFAVORITE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CFavorite
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *labelIP;
    QLineEdit *editIP;
    QPushButton *buttonOk;

    void setupUi(QWidget *CFavorite)
    {
        if (CFavorite->objectName().isEmpty())
            CFavorite->setObjectName(QStringLiteral("CFavorite"));
        CFavorite->resize(240, 86);
        gridLayoutWidget = new QWidget(CFavorite);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(9, 29, 221, 51));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        labelIP = new QLabel(gridLayoutWidget);
        labelIP->setObjectName(QStringLiteral("labelIP"));

        gridLayout->addWidget(labelIP, 0, 0, 1, 1);

        editIP = new QLineEdit(gridLayoutWidget);
        editIP->setObjectName(QStringLiteral("editIP"));
        editIP->setMaxLength(80);

        gridLayout->addWidget(editIP, 0, 1, 1, 1);

        buttonOk = new QPushButton(gridLayoutWidget);
        buttonOk->setObjectName(QStringLiteral("buttonOk"));

        gridLayout->addWidget(buttonOk, 1, 0, 1, 2);


        retranslateUi(CFavorite);

        QMetaObject::connectSlotsByName(CFavorite);
    } // setupUi

    void retranslateUi(QWidget *CFavorite)
    {
        CFavorite->setWindowTitle(QApplication::translate("CFavorite", "Form", 0));
        labelIP->setText(QApplication::translate("CFavorite", "IP:Port", 0));
        buttonOk->setText(QApplication::translate("CFavorite", "Action", 0));
    } // retranslateUi

};

namespace Ui {
    class CFavorite: public Ui_CFavorite {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CFAVORITE_H
