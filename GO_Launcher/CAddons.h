#ifndef CADDONS_H
#define CADDONS_H

#include <QVector>

#include "Style/CCustomWindow.h"

class QListWidgetItem;

namespace Ui {
    class CAddons;
}

class CAddons : public CCustomWindow
{
    Q_OBJECT

public:
    explicit CAddons(QWidget *parent = 0);
    ~CAddons();

    void translate();

private:
    struct Addon
    {
        QString          m_Name;
        QListWidgetItem *m_ptrAddon;
        bool             m_isEnabled;

        Addon() : m_Name(""), m_ptrAddon(NULL), m_isEnabled(false) {}
        Addon(QString name, QListWidgetItem *addon, bool enabled) : m_Name(name), m_ptrAddon(addon), m_isEnabled(enabled) {}
    };

    void loadAddonsList();
    void initConnections();

    Ui::CAddons *ui;
    QVector<Addon> m_AddonList;

private slots:
    void onAddonDoubleClicked(const QModelIndex &index);
};

#endif // CADDONS_H
