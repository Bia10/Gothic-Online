#include <QDir>
#include <QFile>
#include <QFileInfo>

#include "PCH.h"

CAddons::CAddons(QWidget *parent) :
    CCustomWindow(QString(":/img/go_widget.png"), parent, BUTTON_CLOSE),
    ui(new Ui::CAddons)
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
    ui->setupUi(this);

    initConnections();
    loadAddonsList();
}

CAddons::~CAddons()
{
#ifdef DEBUG_MODE
    LOG(__FUNCTION__)
#endif
    delete ui;
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Public method
//-------------------------------------------------------------------------------------------------------------------------------

void CAddons::translate()
{
    setWindowTitle(TRANSLATE("L_ADDONS"));
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Private method
//-------------------------------------------------------------------------------------------------------------------------------

void CAddons::loadAddonsList()
{
    QDir addonDirectory(DATA_PATH);
    addonDirectory.setFilter(QDir::Files);
    addonDirectory.setSorting(QDir::Name);

    int index = 0;

    LOG("[info] Loading addons list")

    for (QString &addon : addonDirectory.entryList())
    {
        LOG("[addon] %s", addon.toStdString().c_str())

        int posExt = addon.lastIndexOf(".");
        QString fileExt = addon.mid(posExt).toLower();

        if (fileExt == ".vdf")
        {
            ui->listStatus->addItem("ON");
            ui->listStatus->item(index)->setTextColor(QColor(0, 255, 0));

            addon.truncate(posExt);
            ui->listAddons->addItem(addon);
            m_AddonList.append(Addon(addon, ui->listAddons->item(index), true));

            ++index;
        }
        else if (fileExt == ".disabled")
        {
            ui->listStatus->addItem("OFF");
            ui->listStatus->item(index)->setTextColor(QColor(255, 0, 0));

            addon.truncate(posExt);
            ui->listAddons->addItem(addon);
            m_AddonList.append(Addon(addon, ui->listAddons->item(index), false));

            ++index;
        }
    }

    LOG("[info] Addons loaded!")
}

void CAddons::initConnections()
{
    connect(this, SIGNAL(Style_quit()),
            this, SLOT(hide()));

    connect(ui->listAddons, SIGNAL(doubleClicked(const QModelIndex&)),
            this, SLOT(onAddonDoubleClicked(const QModelIndex&)));
}

//-------------------------------------------------------------------------------------------------------------------------------
//  Private slots
//-------------------------------------------------------------------------------------------------------------------------------

void CAddons::onAddonDoubleClicked(const QModelIndex &index)
{
    Addon &addon = m_AddonList[index.row()];

    addon.m_isEnabled = !addon.m_isEnabled;

    if (addon.m_isEnabled)
    {
        if (!QFile::rename(DATA_PATH + addon.m_Name + ".vdf.disabled", DATA_PATH + addon.m_Name + ".vdf"))
        {
            CMessageBox::warrning(TRANSLATE("L_ADDONS"), TRANSLATE("A_ERR_01"));
            return;
        }

        ui->listStatus->item(index.row())->setTextColor(QColor(0, 255, 0));
        ui->listStatus->item(index.row())->setText("ON");

    }
    else
    {
        if (!QFile::rename(DATA_PATH + addon.m_Name + ".vdf", DATA_PATH + addon.m_Name + ".vdf.disabled"))
        {
            CMessageBox::warrning(TRANSLATE("L_ADDONS"), TRANSLATE("A_ERR_02"));
            return;
        }

        ui->listStatus->item(index.row())->setTextColor(QColor(255, 0, 0));
        ui->listStatus->item(index.row())->setText("OFF");
    }
}
